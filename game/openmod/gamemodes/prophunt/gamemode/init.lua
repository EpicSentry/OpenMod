--========== Copyleft � 2010, Team Sandbox, Some rights reserved. ===========--
--
-- Purpose:
--
--===========================================================================--

include( "shared.lua" )

local PLAYER_SOUNDS_CITIZEN = 0
local PLAYER_SOUNDS_COMBINESOLDIER = 1
local PLAYER_SOUNDS_METROPOLICE = 2

function GM:AddLevelDesignerPlacedObject( pEntity )
end

function GM:AllowDamage( pVictim, info )
end

function GM:CanEnterVehicle( pPlayer, pVehicle, nRole )
end

function GM:CanHavePlayerItem( pPlayer, pItem )
  if ( cvar.FindVar( "mp_weaponstay" ):GetInt() > 0 ) then
    if ( pPlayer:Weapon_OwnsThisType( pItem:GetClassname(), pItem:GetSubType() ) ) then
	  return false;
	end
  end
end

function GM:CanPlayerHearPlayer( pListener, pTalker, bProximity )
end

function GM:CheatImpulseCommands( pPlayer, iImpulse )
end

function GM:CheckChatForReadySignal( pPlayer, chatmsg )
end

function GM:CleanUpMap()
end

function GM:ClientConnected( pEntity, pszName, pszAddress, reject, maxrejectlen )
end

function GM:ClientDisconnected( pClient )
end

function GM:FlItemRespawnTime( pItem )
  return cvar.FindVar( "sv_hl2mp_item_respawn_time" ):GetFloat();
end

function GM:FlPlayerFallDamage( pPlayer )
end

function GM:FlPlayerSpawnTime( pPlayer )
end

function GM:FPlayerCanRespawn( pPlayer )
end

function GM:FPlayerCanTakeDamage( pPlayer, pAttacker )
end

function GM:FShouldSwitchWeapon( pPlayer, pWeapon )
end

function GM:GiveDefaultItems( pPlayer )
	pPlayer:EquipSuit();
end

function GM:Host_Say( pPlayer, p, teamonly )
end

function GM:InitHUD( pPlayer )
end

function GM:ItemShouldRespawn( pItem )
end

function GM:LevelInit( strMapName, strMapEntities, strOldLevel, strLandmarkName, loadGame, background )
end

function GM:NetworkIDValidated( strUserName, strNetworkID )
end

function GM:PlayerCanHearChat( pListener, pSpeaker )
end

function GM:PlayerCanPickupObject( pObject, massLimit, sizeLimit )
end

function GM:PlayerDeathSound( info )
end

function GM:PlayerDeathThink( pPlayer )
end

function GM:PlayerEntSelectSpawnPoint( pHL2MPPlayer )
end

function GM:PlayerGotItem( pPlayer, pItem )
end

function GM:PlayerInitialSpawn( pPlayer )
	pPlayer.m_bDrawViewmodel = false
end

function GM:PlayerPickupObject( pHL2MPPlayer, pObject, bLimitMassAndSize )
	if pObject == NULL then
		return false
	end
	local modelname = pObject:GetModelName()
	
	_R.CBaseEntity.PrecacheModel(modelname)
	pHL2MPPlayer:SetModel(modelname)
	return false
end

function GM:PlayerSpawn( pPlayer )
end

function GM:PlayerThink( pPlayer )
end

function GM:RemoveLevelDesignerPlacedObject( pEntity )
end

function GM:RestartGame()
end

function GM:ServerActivate( edictCount, clientMax )
end

function GM:ShouldHideServer()
end

function GM:VecItemRespawnSpot( pItem )
end

function GM:VecItemRespawnAngles( pItem )
end

function GM:WeaponShouldRespawn( pWeapon )
end

function GM:Weapon_Equip( pPlayer, pWeapon )
end
