#include "CSSStyleSheet.h"

#include "../../assembly/builder/CSSRuleBuilder.h"

namespace Newtoo
{

    CSSStyleSheet::CSSStyleSheet(CSSRule* aOwnerRule)
        :mOwnerRule(aOwnerRule)
    {}

    StyleSheet* CSSStyleSheet::clone()
    {
        return new CSSStyleSheet(*this);
    }

#define QUOTE '\"'
#define ALTERNATIVE_QUOTE '\''
#define CLOSE_RULE_CHAR '}'
#define CLOSE_SINGLE_RULE_CHAR ';'
#define OPEN_RULE_CHAR '{'

#define noInRule deep == 0

#define split(ind) if(ind + 1 < (int)size) { \
DOMString next = target->substring(ind + 1, target->size() - ind - 1); \
*target = target->substring(0, ind); \
rules.push_back(next); \
target = &rules.back(); i = 0; continue; } else { return rules; }

    std::vector<DOMString> toRuleList(DOMString text)
    {
        /*
            Тут был баг. Если написать после последнего правила лишние
            символы, Newtoo создаст лишний CSSStyleRule с неверными
            входными данными (нету кавычек) и вылетит.
            Я его исправил ниже
        */
        do
        {
            if(text.endsWithChar(CLOSE_RULE_CHAR)
            or text.endsWithChar(CLOSE_SINGLE_RULE_CHAR))
                break;
            text = text.substring(0, text.size() - 2);
        }
        while(true);

        std::vector<DOMString> rules;
        rules.push_back(text);

        DOMString* target = &rules.back();

        bool inString = false;
        unsigned int deep = 0;
        char quote = 0;

        signed long i = 0;

        while(true)
        {
            unsigned long size = target->size();

            if(i >= (int)size)
                break;

            char c = target->item(i);

            if(!inString)
            {
                if(c == QUOTE or c == ALTERNATIVE_QUOTE)
                {
                    inString = true;
                    quote = c;
                    continue;
                }
                else if(c == OPEN_RULE_CHAR)
                {
                    deep++;
                }
                else if(c == CLOSE_RULE_CHAR)
                {
                    deep--;
                    if(noInRule)
                    {
                        split(i);
                    }
                }
                else if(c == CLOSE_SINGLE_RULE_CHAR and noInRule)
                {
                    split(i);
                }
            } else
            {
                if(c == quote)
                {
                    inString = false;
                }
            }

            i++;
        }
        return rules;
    }

    unsigned long CSSStyleSheet::insertRule(DOMString rule, unsigned long index)
    {
        std::vector<DOMString> rules = toRuleList(rule);

        for(unsigned i = 0; i < rules.size(); i++)
            cssRules().insertRule(CSSRuleBuilder::createRule(rules[i]), index + i);

        return index;
    }

    RaisesExceptionVoid CSSStyleSheet::deleteRule(unsigned long index)
    {
        if(index >= cssRules().length())
            return RaisesExceptionVoid(DOMException(IndexSizeError));

        cssRules().removeRule(index);

        return RaisesExceptionVoid();
    }

    void CSSStyleSheet::appendCSS(DOMString rules)
    {
        std::vector<DOMString> list = toRuleList(rules);

        for(unsigned i = 0; i < list.size(); i++)
            cssRules().appendRule(CSSRuleBuilder::createRule(list[i]));
    }

}
