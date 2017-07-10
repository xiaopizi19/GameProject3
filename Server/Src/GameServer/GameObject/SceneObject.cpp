﻿#include "stdafx.h"
#include "SceneObject.h"
#include "..\GameService.h"

CSceneObject::CSceneObject()
{
    m_dwProxyConnID = 0;
    m_dwObjState = 0;
    m_dwHp = 0;
    m_dwClientConnID = 0;
    m_uID = 0;
    m_bEnter = FALSE;
    m_bChanged = FALSE;
}

CSceneObject::~CSceneObject()
{

}

//BOOL CSceneObject::StartSkill()
//{
	//UINT32 SkillID;
	//UINT32 targets[1];
	//BOOL bKill;

	//需要检

	/*
	1. 技能是否存在。
	2. 技能CD是否可以施放。
	3. 技能是否可以打中指定的目标.
	4. 玩家是否增加buff.


	//技能分类。
	1. 立即攻击技有, 只有CD, 方向， 
	2. 增加buff的技能， 就增加buff.
	3. 位移技能， 需要带位移长度。
	4. 波次技能。 就是每一帆的收集攻击的对象.就是分成两部分。
	5. 时长技能。 放出去就有位移，由客户端自己算打中谁，服务器验证一下。就转发。



	//实现设想两种。
	1. 一放一个技能，就new一个技能对象。
	在线这个技能对象里就update，不断的update，由技能本身去改变状态，寻找攻击目标.


	2. 服务器不管过程。
	由客户端去驱动攻击状态。
	*/


	/*
	buff类型, buff的特效就不用管了。
	1. 增加属性, 加上就上， 减掉就取消。
	2. 修改状态, 
	3. 每秒造成伤害
	4. 攻击时增加伤害
	5. 持线伤害

	玩家需要对应的状态
	1. 无敌。
	2. 不能移动。
	*/

	//return TRUE;
//}

BOOL CSceneObject::SetConnectID(UINT32 dwProxyID, UINT32 dwClientID)
{
	m_dwProxyConnID = dwProxyID;
	m_dwClientConnID = dwClientID;

	return TRUE;
}

// BOOL CPlayerObject::AttackEvent()
// {
// 	UINT32  SkillID;
// 	UINT32  targets[];
// 
// 
// }


BOOL CSceneObject::SendProtoBuf(UINT32 dwMsgID, const google::protobuf::Message& pdata)
{
	return ServiceBase::GetInstancePtr()->SendMsgProtoBuf(m_dwProxyConnID, dwMsgID, GetObjectID(), m_dwClientConnID, pdata);
}

BOOL CSceneObject::OnUpdate( UINT32 dwTick )
{

	return TRUE;
}

UINT32 CSceneObject::GetHp()
{
    return m_dwHp;
}

VOID CSceneObject::AddHp( UINT32 dwValue )
{
    m_dwHp += dwValue;
}

VOID CSceneObject::SubHp( UINT32 dwValue )
{
    if(m_dwHp <= dwValue)
    {
        m_dwHp = 0;
    }

    m_dwHp -= dwValue;
}

UINT64 CSceneObject::GetObjectID()
{
    return m_uID;
}

BOOL CSceneObject::IsEnterCopy()
{
    return m_bEnter;
}

VOID CSceneObject::SetEnterCopy()
{
	m_bEnter = TRUE;
}

BOOL CSceneObject::SaveNewObject( ObjectNewNty &Nty )
{
    return TRUE;
}

BOOL CSceneObject::SaveUpdateObject( ObjectUpdateNty &Nty )
{
    if(!m_bChanged)
    {
        return TRUE;
    }

    ObjectUpdate *pUpdate = Nty.add_updatelist();
    pUpdate->set_roleid(m_uID);
    pUpdate->set_x(m_Pos.x);
    pUpdate->set_z(m_Pos.z);
    pUpdate->set_d(m_Pos.d);
    pUpdate->set_y(m_Pos.y);
    pUpdate->set_objstate(m_dwObjState);

    return TRUE;
}

BOOL CSceneObject::IsDie()
{
    if(m_dwHp <= 0)
    {
        return TRUE;
    }

    return FALSE;
}

VOID CSceneObject::SetChanged()
{
    m_bChanged = TRUE;
}
