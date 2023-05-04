---
-- Represents a player in the Monopoly game.
-- @classmod Player

---
-- Constructs a new Player object.
-- @function Player:new
-- @tparam string name The name of the player.
-- @tparam Money startingMoney The starting money of the player.
-- @treturn Player The newly created Player object.

---
-- Adds money to the player's balance.
-- @function Player:addMoney
-- @tparam Money new_cash The amount of money to add.
-- @treturn bool Whether the money was added successfully.

---
-- Checks if the player can build a structure on a property of the given color.
-- @function Player:canBuildStructure
-- @tparam PropertyColor color_id The color of the property to check.
-- @treturn bool Whether the player can build a structure on a property of the given color.

---
-- Buys a property and adds it to the player's list of owned properties.
-- @function Player:buyProperty
-- @tparam Landable property The property to buy.
-- @treturn bool Whether the property was bought successfully.

---
-- Adds a property to the player's list of owned properties.
-- @function Player:addProperty
-- @tparam Landable property The property to add.
-- @treturn bool Whether the property was added successfully.

---
-- Takes money from the player's balance.
-- @function Player:takeMoney
-- @tparam Money debt The amount of money to take.
-- @treturn bool Whether the money was taken successfully.

---
-- Sets the player's balance to the given amount.
-- @function Player:setMoney
-- @tparam Money cash The amount of money to set the balance to.

---
-- Sets whether the player is currently in jail.
-- @function Player:setInJail
-- @tparam bool inJail Whether the player is in jail.

---
-- Checks whether the player is currently in jail.
-- @function Player:inJail
-- @treturn bool Whether the player is in jail.

---
-- Sets the player's position on the board.
-- @function Player:setPosition
-- @tparam int position The position to set.

---
-- Gets the player's position on the board.
-- @function Player:getPosition
-- @treturn int The player's position.

---
-- Notifies the player that it is their turn.
-- @function Player:notifyTurn

---
-- Notifies the player of a decision they must make.
-- @function Player:notifyDecision
-- @tparam MonopolyEvent event The event that requires the player's decision.
-- @treturn MonopolyDecision The player's decision.


local chance_cards = {
    {
        text = "Advance to Go (Collect $400)",
        action = function(player)
            -- TODO: Implement the action for this Chance card
            player:addMoney(200)
            --debug
            print(string.format("[LUA] : added 200 to player: %s", player:getName()))
        end
    },
    {
        text = "Advance to Illinois Ave. - If you pass Go, collect $400",
        action = function(player)
            -- TODO: Implement the action for this Chance card
            
        end
    },
    {
        text = "Advance to St. Charles Place – If you pass Go, collect $200",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Advance token to nearest Utility. If unowned, you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Advance token to the nearest Railroad and pay owner twice the rental to which they are otherwise entitled. If Railroad is unowned, you may buy it from the Bank.",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Bank pays you dividend of $50",
        action = function(player)
            -- TODO: Implement the action for this Chance card
            player:addMoney(50)
        end
    },
    {
        text = "Get Out of Jail Free – This card may be kept until needed, or sold",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Go Back 3 Spaces",
        action = function(player)
            -- TODO: Implement the action for this Chance card
            engine_move(-3)
            print(string.format("[LUA] : moved player (%s), back 3 spaces", player:getName()))

        end
    },
    {
        text = "Go to Jail – Go directly to Jail – Do not pass Go, do not collect $200",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Make general repairs on all your property – For each house pay $25 – For each hotel $100",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Pay poor tax of $15",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Take a trip to Reading Railroad – If you pass Go, collect $200",
        action = function(player)
            -- TODO: Implement the action for this Chance card
            -- TODO: Implement the action for this Chance card

        end
    },
    {
        text = "Take a walk on the Boardwalk – Advance token to Boardwalk",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "You have been elected Chairman of the Board – Pay each player $50",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Your building loan matures – Collect $150",
        action = function(player)
            -- TODO: Implement the action for this Chance card
            player:addMoney(150)
            --debug
            print(string.format("[LUA] : added 150 to player: %s", player:getName()))
        end
    },
    {
        text = "You have won a crossword competition - Collect $100",
        action = function(player)
            -- TODO: Implement the action for this Chance card
            player:addMoney(100)
            --debug
            print(string.format("[LUA] : added 100 to player: %s", player:getName()))
        end
    }
}

--@tparam player Player
function PullChanceCard(player)
    local card = chance_cards[random(1, #chance_cards)]
    card.action(player)
    print(string.format("LUA FUNCTION [PullChanceCard]: EXECUTED FOR %s\nCARD: %s\n", player:getName(), card.text));
end
