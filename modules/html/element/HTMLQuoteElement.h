#pragma once

#include "HTMLElement.h"

namespace Newtoo
{

    class HTMLQuoteElement : public HTMLElement
    {
    public:

        HTMLQuoteElement();
        HTMLQuoteElement(DOMString aNamespace, DOMString qualifiedName, DOMString aPrefix = "");

        CSSStyleDeclaration userAgentStyle() override;

        Node* cloneNode(bool deep = false) override;

        DOMString cite()                                { return getAttribute("cite"); }
        void setCite(DOMString aCite)                   { setAttribute("cite", aCite); }

        HTMLQuoteElement(HTMLQuoteElement& reference, bool deep)
            :HTMLElement(reference, deep)
        {}

    private:

    };

}
