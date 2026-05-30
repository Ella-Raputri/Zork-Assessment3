#ifndef ZOORK_CELLTYPE_H
#define ZOORK_CELLTYPE_H

#include <string>
#include <vector>
#include <memory>
#include "../../entity/item/Item.h"
#include "../../utils/Color.h"

enum class CellType {
    Floor,  
    Door,  
    Impassable,
    Restricted
};

class Cell {
    protected: 
        CellType type;
        char symbol;
        std::string description;
        std::string regionTag;  // e.g. "house", "garden"
        bool passable;
        std::string color;
        std::vector<std::shared_ptr<Item>> items;

    public: 
        Cell();

        Cell(
            CellType type,
            char symbol,
            const std::string& description,
            const std::string& regionTag,
            bool passable,
            const std::string& color
        );

        virtual ~Cell() = default;

        CellType getType() const;
        char getSymbol() const;
        virtual std::string getDescription() const;
        std::string getRegionTag() const;
        virtual bool isPassable() const;
        std::string getColor() const;

        void setType(CellType);
        void setSymbol(char);
        void setDescription(const std::string&);
        void setRegionTag(const std::string&);
        void setPassable(bool);
        void setColor(const std::string&);

        void addItem(std::shared_ptr<Item> item);
        std::shared_ptr<Item> getItemById(const std::string& itemId);
        std::shared_ptr<Item> getItemByName(const std::string& itemName);
        std::shared_ptr<Item> retrieveItem(const std::string& itemName);
        bool hasItems() const;
        const std::vector<std::shared_ptr<Item>>& getItems() const;
};

#endif //ZOORK_CELLTYPE_H