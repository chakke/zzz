//
//  GameType.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#ifndef GameType_hpp
#define GameType_hpp

#include "cocos2d.h"

namespace game_model
{
    class GameType
    {
    public:
        static const GameType __TAI_XIU__;
        static const GameType __POKER__;
        static const GameType __TIEN_LEN_MIEN_NAM__;
        static const GameType __TIEN_LEN_MIEN_BAC__;
        static const GameType __SAM__;
        static const GameType __TIEN_LEN_DEM_LA__;
        static const GameType __BA_CAY__;
        static const GameType __TA_LA__;
        static const GameType __LIENG__;
        static const GameType __XI_TO__;
        static const GameType __MAU_BINH__;
        static const GameType __XOC_DIA__;
        static const GameType __CHAN__;
        
        static const std::vector<const GameType*>* allTypes();
        
    private:
        GameType(const int& game_id, const int& mul_fee, const int& mul_join);
        
    public:
        const int _game_id;
        const int _mul_fee;
        const int _mul_join;
    };
};

#endif /* GameType_hpp */
