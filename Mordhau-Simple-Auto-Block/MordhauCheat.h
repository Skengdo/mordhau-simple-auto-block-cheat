#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Utils.h"
#include "SDK.hpp"
#include "../SDK/Mordhau_CoreUObject_functions.cpp"
#include "../SDK/Mordhau_Engine_functions.cpp"
#include "../SDK/Mordhau_Mordhau_functions.cpp"
#include "../SDK/Mordhau_Basic.cpp"

using namespace SDK;

namespace Utils
{
	namespace Maths
	{
		float WorldDistance( const FVector& vector, const FVector& Target )
		{
			return float( sqrtf( powf( vector.X - Target.X, 2.0 ) + powf( vector.Y - Target.Y, 2.0 ) + powf( vector.Z - Target.Z, 2.0 ) ) );
		}
	}
}

void __stdcall init_sdk( )
{
	Utils::Variables::ImageBase = ( unsigned __int64 )GetModuleHandle( nullptr );
	GetModuleInformation( GetCurrentProcess( ), ( HMODULE )Utils::Variables::ImageBase, &Utils::Variables::ImageModuleInfo, sizeof( Utils::Variables::ImageModuleInfo ) );

	const auto gname_addr = Utils::Pattern::FindPattern( ( PBYTE )Utils::Variables::ImageBase, Utils::Variables::ImageModuleInfo.SizeOfImage, ( PBYTE )"\x48\x8B\x05\x00\x00\x00\x00\x48\x85\xC0\x75\x5F", ( CHAR* )"xxx????xxxxx", 0 );
	auto offset = *( uint32_t* )( gname_addr + 3 );
	SDK::FName::GNames = ( SDK::TNameEntryArray* )( *( uintptr_t* )( gname_addr + 7 + offset ) );

	const auto objects_addr = Utils::Pattern::FindPattern( ( PBYTE )Utils::Variables::ImageBase, Utils::Variables::ImageModuleInfo.SizeOfImage, ( PBYTE )"\x4C\x8B\x15\x00\x00\x00\x00\x8D\x43\x01", ( CHAR* )"xxx????xxx", 0 );
	offset = *( int32_t* )( objects_addr + 3 );
	SDK::TUObjectArray::g_objects = ( uintptr_t )( objects_addr + 7 + offset ) - ( uintptr_t )GetModuleHandleA( 0 );

	const auto total_objects_addr = Utils::Pattern::FindPattern( ( PBYTE )Utils::Variables::ImageBase, Utils::Variables::ImageModuleInfo.SizeOfImage, ( PBYTE )"\x4C\x8B\x15\x00\x00\x00\x00\x8D\x43\x01", ( CHAR* )"xxx????xxx", 0 );
	offset = *( int32_t* )( total_objects_addr + 3 );
	SDK::TUObjectArray::g_total_objects = ( uintptr_t )( total_objects_addr + 7 + offset ) - ( uintptr_t )GetModuleHandleA( 0 );
}

void __stdcall init_cheat( )
{
	init_sdk( );

	const auto addr_UWorld = Utils::Pattern::FindPattern( ( PBYTE )Utils::Variables::ImageBase, Utils::Variables::ImageModuleInfo.SizeOfImage, ( PBYTE )"\x48\x8B\x1D\x00\x00\x00\x00\x48\x85\xDB\x74\x3B\x41\xB0\x01", ( CHAR* )"xxx????xxxxxxxx", 0 );
	const auto p_UWorld = *reinterpret_cast< UWorld** >( addr_UWorld + 7 + *reinterpret_cast< uint32_t* > ( addr_UWorld + 3 ) );

	while ( true )
	{
		if ( GetAsyncKeyState( VK_F12 ) )
			FreeLibraryAndExitThread( Utils::Variables::ImageModuleHandle, 0 );

		const auto local_player = p_UWorld->OwningGameInstance->LocalPlayers [ 0 ];

		if ( local_player == nullptr )
			continue;

		const auto local_player_controller = local_player->PlayerController;

		if ( local_player_controller == nullptr )
			continue;

		const auto local_actor = static_cast< AActor* >( local_player_controller->AcknowledgedPawn );

		if ( local_actor == nullptr )
			continue;

		const auto local_root_comp = local_actor->RootComponent;

		if ( local_root_comp == nullptr )
			continue;

		const auto local_mordhau_character = static_cast< AMordhauCharacter* >( local_actor );

		if ( local_mordhau_character == nullptr )
			continue;

		const auto local_mordhau_player_state = static_cast< AMordhauPlayerState* >( local_mordhau_character->PlayerState );

		if ( local_mordhau_player_state == nullptr )
			continue;

		for ( auto i = 0u; i < p_UWorld->PersistentLevel->actors.Num( ); i++ )
		{
			const auto curr_actor = p_UWorld->PersistentLevel->actors [ i ];

			if ( curr_actor == nullptr || curr_actor == local_actor )
				continue;

			if ( !curr_actor->IsA( AMordhauCharacter::StaticClass( ) ) )
				continue;

			const auto curr_mordau_character = static_cast< AMordhauCharacter* >( curr_actor );

			if ( curr_mordau_character == nullptr )
				continue;

			const auto curr_mordau_player_state = static_cast< AMordhauPlayerState* >( curr_mordau_character->PlayerState );

			if ( curr_mordau_player_state == nullptr )
				continue;

			if ( curr_mordau_player_state->Team == local_mordhau_player_state->Team )
				continue;

			const auto curr_actor_root_comp = curr_actor->RootComponent;

			if ( curr_actor_root_comp == nullptr )
				continue;

			float distance_from_me = Utils::Maths::WorldDistance( local_root_comp->RelativeLocation, curr_actor_root_comp->RelativeLocation ) / 100.f;

			if ( distance_from_me < 3.f )
			{
				const auto current_motion = curr_mordau_character->Motion;

				if ( current_motion == nullptr )
					continue;

				if ( current_motion->IsA( UAttackMotion::StaticClass( ) ) && static_cast< UAttackMotion* >( current_motion )->Stage == EAttackStage::Release )
				{
					local_mordhau_character->RequestParry( EBlockType::Regular, 1 );
				}
			}
		}

		std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
	}
}


