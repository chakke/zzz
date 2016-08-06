//
//  GameType.cpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#include "GameType.hpp"

namespace game_model
{
    const GameType GameType::__TAI_XIU__(12,0,0);
    const GameType GameType::__POKER__(4,2,10);
    const GameType GameType::__TIEN_LEN_MIEN_NAM__(10,0,0);
    const GameType GameType::__TIEN_LEN_MIEN_BAC__(1,0,0);
    const GameType GameType::__SAM__(7,0,0);
    const GameType GameType::__TIEN_LEN_DEM_LA__(2,0,0);
    const GameType GameType::__BA_CAY__(3,0,5);
    const GameType GameType::__TA_LA__(0,0,0);
    const GameType GameType::__LIENG__(6,0,10);
    const GameType GameType::__XI_TO__(5,0,10);
    const GameType GameType::__MAU_BINH__(8,0,0);
    const GameType GameType::__XOC_DIA__(11,0,0);
    const GameType GameType::__CHAN__(9,0,0);
    
    std::vector<const GameType*>* _all_types = nullptr;
    
    GameType::GameType(const int& game_id, const int& mul_fee, const int& mul_join)
    :_game_id(game_id), _mul_fee(mul_fee), _mul_join(mul_join)
    {
        if (!_all_types) {
            _all_types = new std::vector<const GameType*>();
        }
        _all_types->push_back(this);
    }
    
    const std::vector<const GameType*>* GameType::allTypes()
    {
        return _all_types;
    }
    
}