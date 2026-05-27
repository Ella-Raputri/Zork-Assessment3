#ifndef ZOORK_CLUEITEM_H
#define ZOORK_CLUEITEM_H

#include "Item.h"

class ClueItem : public Item {
public:
    ClueItem(const std::string &n,
             const std::string &d,
             const std::string &id);

    void use() override;
};

#endif //ZOORK_CLUEITEM_H