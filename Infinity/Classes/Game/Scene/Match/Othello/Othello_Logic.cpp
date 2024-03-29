//
//  Othello_Logic.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "Othello_Logic.h"
#include "Match_Map.h"
#include "Unit_Black.h"
#include "Unit_White.h"

bool Othello_Logic::Logic_AddUnit(Match_Map* cur_Map, const cocos2d::CCPoint &touchPos, int& x, int& y, int tag)
{
    if(cur_Map->GetEmptyTile_FromTouch(touchPos, &x, &y) == true)
    {
        //CCLOG("Empty Tile x : %d, y : %d", x, y);
        return Logic_CheckInterUnit(cur_Map, x, y, tag);
    }
    else
    {
        //CCLOG("Dont' Exist Empty Tile");
        return false;
    }
}

bool Othello_Logic::Logic_CheckInterUnit(Match_Map *cur_Map, int index_X, int index_Y, int tag)
{
    bool ret = false;
    
    //CCLOG("x : %d, y : %d, tag : %d", index_X, index_Y, tag);
    
    ret = ret | Logic_CheckInterUnit_Hori_Right(cur_Map, index_X, index_Y, tag);
    ret = ret | Logic_CheckInterUnit_Hori_Left(cur_Map, index_X, index_Y, tag);
    ret = ret | Logic_CheckInterUnit_Verti_Up(cur_Map, index_X, index_Y, tag);
    ret = ret | Logic_CheckInterUnit_Verti_Down(cur_Map, index_X, index_Y, tag);
    ret = ret | Logic_CheckInterUnit_DirLR_Up(cur_Map, index_X, index_Y, tag);
    ret = ret | Logic_CheckInterUnit_DirLR_Down(cur_Map, index_X, index_Y, tag);
    ret = ret | Logic_CheckInterUnit_DirRL_Up(cur_Map, index_X, index_Y, tag);
    ret = ret | Logic_CheckInterUnit_DirRL_Down(cur_Map, index_X, index_Y, tag);
    
    return ret;
}

bool Othello_Logic::Logic_CheckInterUnit_AfterLogic(Match_Map* cur_Map, vector<int> &list_InterUnit, int index_X, int index_Y, int tag)
{
    if(list_InterUnit.size() > 0)
    {
        for(int i=0; i<list_InterUnit.size(); ++i)
        {
            int index = list_InterUnit[i];
            cur_Map->RemoveUnit(index);
            cur_Map->SetUnit_ToMap(CreateUnit(tag), cur_Map->GetConvertedTileIndex_X(index), cur_Map->GetConvertedTileIndex_Y(index));
        }
        cur_Map->SetUnit_ToMap(CreateUnit(tag), index_X, index_Y);
        return true;
    }
    else return false;
}

Unit_Base* Othello_Logic::CreateUnit(int tag)
{
    if(tag == 0) return Unit_Black::create();
    else if(tag == 1) return Unit_White::create();
    else return NULL;
}

bool Othello_Logic::Logic_CheckInterUnit_Hori_Right(Match_Map* cur_Map, int index_X, int index_Y, int tag)
{
    vector<int> list_InterUnit;
    
    for(int i = index_X + 1; i < cur_Map->GetTileCount_Width(); ++i)
    {
        int tileTag = cur_Map->GetTileTag(i, index_Y);
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(i, index_Y));
    }
    
    return false;
}

bool Othello_Logic::Logic_CheckInterUnit_Hori_Left(Match_Map* cur_Map, int index_X, int index_Y, int tag)
{
    vector<int> list_InterUnit;
    
    for(int i = index_X - 1; i >= 0; --i)
    {
        int tileTag = cur_Map->GetTileTag(i, index_Y);
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(i, index_Y));
    }
    
    return false;
}

bool Othello_Logic::Logic_CheckInterUnit_Verti_Up(Match_Map* cur_Map, int index_X, int index_Y, int tag)
{
    vector<int> list_InterUnit;
    
    for(int i = index_Y + 1; i < cur_Map->GetTileCount_Height(); ++i)
    {
        int tileTag = cur_Map->GetTileTag(index_X, i);
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(index_X, i));
        
        //CCLOG("index_X : %d, i : %d, tag : %d", index_X, i, tag);
    }
    
    return false;
}

bool Othello_Logic::Logic_CheckInterUnit_Verti_Down(Match_Map* cur_Map, int index_X, int index_Y, int tag)
{
    vector<int> list_InterUnit;
    
    for(int i = index_Y - 1; i >= 0; --i)
    {
        int tileTag = cur_Map->GetTileTag(index_X, i);
        //CCLOG("titleTag : %d", tileTag);
        
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(index_X, i));
        
        //CCLOG("index_X : %d, i : %d, tag : %d", index_X, i, tag);
    }
    
    return false;
}

bool Othello_Logic::Logic_CheckInterUnit_DirLR_Up(Match_Map* cur_Map, int index_X, int index_Y, int tag) //대각선 \방향임.
{
    vector<int> list_InterUnit;
    
    for(int i = 1; i < cur_Map->GetTileCount_Width(); ++i)
    {
        int x = index_X - i;
        int y = index_Y + i;
        
        if(x < 0) return false;
        if(y >= cur_Map->GetTileCount_Height()) return false;
        
        int tileTag = cur_Map->GetTileTag(x, y);
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(x, y));
    }
    
    return false;
}

bool Othello_Logic::Logic_CheckInterUnit_DirLR_Down(Match_Map* cur_Map, int index_X, int index_Y, int tag) //대각선 \방향임.
{
    vector<int> list_InterUnit;
    
    for(int i = 1; i < cur_Map->GetTileCount_Width(); ++i)
    {
        int x = index_X + i;
        int y = index_Y - i;
        
        if(y < 0) return false;
        if(x >= cur_Map->GetTileCount_Width()) return false;
        
        int tileTag = cur_Map->GetTileTag(x, y);
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(x, y));
    }
    
    return false;
}

bool Othello_Logic::Logic_CheckInterUnit_DirRL_Up(Match_Map* cur_Map, int index_X, int index_Y, int tag) //대각선 /방향임.
{
    vector<int> list_InterUnit;
    
    for(int i = 1; i < cur_Map->GetTileCount_Width(); ++i)
    {
        int x = index_X + i;
        int y = index_Y + i;
        
        if(x >= cur_Map->GetTileCount_Width()) return false;
        if(y >= cur_Map->GetTileCount_Height()) return false;
        
        int tileTag = cur_Map->GetTileTag(x, y);
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(x, y));
    }
    
    return false;
}

bool Othello_Logic::Logic_CheckInterUnit_DirRL_Down(Match_Map* cur_Map, int index_X, int index_Y, int tag) //대각선 /방향임.
{
    vector<int> list_InterUnit;
    
    for(int i = 1; i < cur_Map->GetTileCount_Width(); ++i)
    {
        int x = index_X - i;
        int y = index_Y - i;
        
        if(x < 0) return false;
        if(y < 0) return false;
        
        int tileTag = cur_Map->GetTileTag(x, y);
        if(tileTag == tag) return Logic_CheckInterUnit_AfterLogic(cur_Map, list_InterUnit, index_X, index_Y, tag);
        else if(tileTag == -1) return false;
        else list_InterUnit.push_back(cur_Map->GetConvertedTileIndex(x, y));
    }
    
    return false;
}