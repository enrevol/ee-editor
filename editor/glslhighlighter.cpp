#include "glslhighlighter.hpp"
#include "glslcomponent.hpp"

namespace ee {
using Self = GLSLHighlighter;

Self::GLSLHighlighter(QTextDocument* parent)
    : Super(parent)
    , markSensitivity_(Qt::CaseSensitivity::CaseInsensitive) {
    // Default color scheme.
    colors_[GLSLComponent::Normal] = QColor("#000000");
    colors_[GLSLComponent::Comment] = QColor("#808080");
    colors_[GLSLComponent::Number] = QColor("#008000");
    colors_[GLSLComponent::String] = QColor("#800000");
    colors_[GLSLComponent::Operator] = QColor("#808000");
    colors_[GLSLComponent::Identifier] = QColor("#000020");
    colors_[GLSLComponent::Keyword] = QColor("#000080");
    colors_[GLSLComponent::BuiltIn] = QColor("#008080");
    colors_[GLSLComponent::Marker] = QColor("#ffff00");

    keywords_ << "attribute";
    keywords_ << "const";
    keywords_ << "uniform";
    keywords_ << "varying";

    keywords_ << "break";
    keywords_ << "continue";
    keywords_ << "do";
    keywords_ << "for";
    keywords_ << "while";
    keywords_ << "switch";
    keywords_ << "case";
    keywords_ << "default";
    keywords_ << "if";
    keywords_ << "else";

    keywords_ << "in";
    keywords_ << "out";
    keywords_ << "iunout";

    keywords_ << "true";
    keywords_ << "false";

    keywords_ << "discard";
    keywords_ << "return";

    keywords_ << "lowp";
    keywords_ << "mediump";
    keywords_ << "highp";
    keywords_ << "precision";

    keywords_ << "struct";

    types_ << "bool";
    types_ << "int";
    types_ << "float";
    types_ << "double";
    types_ << "void";

    types_ << "mat2";
    types_ << "mat3";
    types_ << "mat4";

    types_ << "vec2";
    types_ << "vec3";
    types_ << "vec4";

    types_ << "bvec2";
    types_ << "bvec3";
    types_ << "bvec4";

    types_ << "ivec2";
    types_ << "ivec3";
    types_ << "ivec4";
}

void Self::setColor(GLSLComponent component, const QColor& color) {
    if (colors_[component] == color) {
        return;
    }
    colors_[component] = color;
    rehighlight();
}

void Self::mark(const QString& text, Qt::CaseSensitivity sensitivity) {
    if (markString_ == text && markSensitivity_ == sensitivity) {
        return;
    }
    markString_ = text;
    markSensitivity_ = sensitivity;
    rehighlight();
}

namespace {
enum class State {
    Start = 0,
    Number = 1,
    Identifier = 2,
    String = 3,
    Comment = 4,
    Regex = 5
};
} // namespace

void Self::highlightBlock(const QString& text) {
    QList<int> bracketPositions;

    auto blockState = previousBlockState();
    auto bracketLevel = blockState >> 4;
    auto state = static_cast<State>(blockState & 15);
    if (blockState < 0) {
        bracketLevel = 0;
        state = State::Start;
    }

    int start = 0;
    int i = 0;
    while (i <= text.length()) {
        auto ch = (i < text.length() ? text.at(i) : QChar());
        auto next = (i < text.length() - 1 ? text.at(i + 1) : QChar());
        auto prev = (i > 0 ? text.at(i - 1) : QChar());

        switch (state) {
        case State::Start:
            start = i;
            if (ch.isSpace()) {
                ++i;
            } else if (ch.isDigit()) {
                ++i;
                state = State::Number;
            } else if (ch.isLetter() || ch == '_') {
                ++i;
                state = State::Identifier;
            } else if (ch == '\'' || ch == '\"') {
                ++i;
                state = State::String;
            } else if (ch == '/' && next == '*') {
                ++i;
                ++i;
                state = State::Comment;
            } else if (ch == '/' && next == '/') {
                i = text.length();
                setFormat(start, text.length(),
                          colors_[GLSLComponent::Comment]);
            } else if (ch == '/' && next != '*') {
                ++i;
                state = State::Regex;
            } else {
                if (not QString("(){}[]").contains(ch)) {
                    setFormat(start, 1, colors_[GLSLComponent::Operator]);
                }
                if (ch == '{' || ch == '}') {
                    if (ch == '{') {
                        ++bracketLevel;
                    } else {
                        --bracketLevel;
                    }
                }
                ++i;
                state = State::Start;
            }
            break;

        case State::Number:
            if (ch.isSpace() || not ch.isDigit()) {
                setFormat(start, i - start, colors_[GLSLComponent::Number]);
                state = State::Start;
            } else {
                ++i;
            }
            break;

        case State::Identifier:
            if (ch.isSpace() ||
                not(ch.isDigit() || ch.isLetter() || ch == '_')) {
                auto token = text.mid(start, i - start).trimmed();
                if (keywords_.contains(token)) {
                    setFormat(start, i - start,
                              colors_[GLSLComponent::Keyword]);
                } else if (types_.contains(token) ||
                           builtIns_.contains(token)) {
                    setFormat(start, i - start,
                              colors_[GLSLComponent::BuiltIn]);
                }
                state = State::Start;
            } else {
                ++i;
            }
            break;

        case State::String:
            if (ch == text.at(start)) {
                if (prev != '\\') {
                    ++i;
                    setFormat(start, i - start, colors_[GLSLComponent::String]);
                    state = State::Start;
                } else {
                    ++i;
                }
            } else {
                ++i;
            }
            break;

        case State::Comment:
            if (ch == '*' && next == '/') {
                ++i;
                ++i;
                setFormat(start, i - start, colors_[GLSLComponent::Comment]);
                state = State::Start;
            } else {
                ++i;
            }
            break;

        case State::Regex:
            if (ch == '/') {
                if (prev != '\\') {
                    ++i;
                    setFormat(start, i - start, colors_[GLSLComponent::String]);
                    state = State::Start;
                } else {
                    ++i;
                }
            } else {
                ++i;
            }
            break;

        default:
            state = State::Start;
            break;
        }
    }

    if (state == State::Comment) {
        setFormat(start, text.length(), colors_[GLSLComponent::Comment]);
    }

    if (not markString_.isEmpty()) {
        int pos = 0;
        int len = markString_.length();
        QTextCharFormat format;
        format.setBackground(colors_[GLSLComponent::Marker]);
        format.setForeground(colors_[GLSLComponent::Normal]);
        while (true) {
            pos = text.indexOf(markString_, pos, markSensitivity_);
            if (pos < 0) {
                break;
            }
            setFormat(pos, len, format);
            ++pos;
        }
    }

    blockState = (static_cast<int>(state) & 15) | (bracketLevel << 4);
    setCurrentBlockState(blockState);
}
} // namespace ee
