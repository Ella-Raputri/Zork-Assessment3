//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "../command/Command.h"
#include "GameObject.h"
#include "../command/NullCommand.h"
#include <memory>

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &);

    Item(const std::string &, const std::string &, std::shared_ptr<Command>);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);

protected:
    std::shared_ptr<Command> useCommand;
};

#endif //ZOORK_ITEM_H
