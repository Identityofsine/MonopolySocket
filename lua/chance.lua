local chance_cards = {
    {
        text = "Advance to Go (Collect $200)",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    },
    {
        text = "Advance to Illinois Ave. - If you pass Go, collect $200",
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
        end
    },
    {
        text = "You have won a crossword competition - Collect $100",
        action = function(player)
            -- TODO: Implement the action for this Chance card
        end
    }
}

function PullChanceCard()
    local card = chance_cards[random(1, #chance_cards)]
    
    return "LUA FUNCTION [PullChanceCard]: EXECUTED"
end

