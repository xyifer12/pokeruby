SlateportCity_ContestLobby_MapScripts:: @ 8155411
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_ContestLobby_MapScript1_OnTransition
	.byte 0

SlateportCity_ContestLobby_MapScript1_OnTransition:: @ 8155417
	call LilycoveCity_ContestLobby_EventScript_TryShowContestReporter
	end

SlateportCity_ContestLobby_EventScript_ContestReceptionist:: @ 815541D
	setvar VAR_0x800B, 7
	setvar VAR_CONTEST_RANK, 2
	call LilycoveCity_ContestLobby_EventScript_1A4E92
	call SlateportCity_ContestLobby_EventScript_155448
	special SetContestTrainerGfxIds
	call LilycoveCity_ContestLobby_EventScript_SetupRivalGfxId
	setvar VAR_CONTEST_LOCATION, 3
	warp MAP_LINK_CONTEST_ROOM1, 255, 7, 5
	waitstate
	end

SlateportCity_ContestLobby_EventScript_155448:: @ 8155448
	lockall
	applymovement 1, SlateportCity_ContestLobby_Movement_1554CC
	waitmovement 0
	playse SE_BRIDGE_WALK
	setmetatile 4, 2, METATILE_Contest_WallShadow, 1
	setmetatile 4, 3, METATILE_Contest_FloorShadow, 1
	special DrawWholeMapView
	applymovement 1, SlateportCity_ContestLobby_Movement_1554CF
	waitmovement 0
	playse SE_BRIDGE_WALK
	setmetatile 4, 2, METATILE_Contest_CounterFlap_Top, 1
	setmetatile 4, 3, METATILE_Contest_CounterFlap_Bottom, 1
	special DrawWholeMapView
	delay 20
	applymovement 1, SlateportCity_ContestLobby_Movement_1554DC
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_ContestLobby_Movement_1554CA
	waitmovement 0
	msgbox LilycoveCity_ContestLobby_Text_ComeThroughHere, MSGBOX_DEFAULT
	closemessage
	applymovement 1, SlateportCity_ContestLobby_Movement_1554D3
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_ContestLobby_Movement_1554C0
	waitmovement 0
	releaseall
	return

SlateportCity_ContestLobby_Movement_1554C0:: @ 81554C0
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

SlateportCity_ContestLobby_Movement_1554CA:: @ 81554CA
	walk_in_place_fastest_left
	step_end

SlateportCity_ContestLobby_Movement_1554CC:: @ 81554CC
	walk_left
	walk_in_place_fastest_down
	step_end

SlateportCity_ContestLobby_Movement_1554CF:: @ 81554CF
	walk_down
	walk_down
	walk_in_place_fastest_up
	step_end

SlateportCity_ContestLobby_Movement_1554D3:: @ 81554D3
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

SlateportCity_ContestLobby_Movement_1554DC:: @ 81554DC
	walk_in_place_fastest_right
	step_end

SlateportCity_ContestLobby_EventScript_Man:: @ 81554DE
	msgbox SlateportCity_ContestLobby_Text_WantToRaiseUltimateMon, MSGBOX_NPC
	end

SlateportCity_ContestLobby_EventScript_Girl:: @ 81554E7
	msgbox SlateportCity_ContestLobby_Text_DoYourFriendsHaveBerries, MSGBOX_NPC
	end

SlateportCity_ContestLobby_EventScript_Woman:: @ 81554F0
	msgbox SlateportCity_ContestLobby_Text_ContestWinnerPostersOnWall, MSGBOX_NPC
	end

SlateportCity_ContestLobby_EventScript_LittleGirl:: @ 81554F9
	lockall
	goto_if_set FLAG_RECEIVED_POKEBLOCK_CASE, SlateportCity_ContestLobby_EventScript_HavePokeblockCase
	applymovement 7, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_ContestLobby_Text_YouCanHavePokeblockCase, MSGBOX_DEFAULT
	giveitem ITEM_POKEBLOCK_CASE
	setflag FLAG_RECEIVED_POKEBLOCK_CASE
	releaseall
	end

SlateportCity_ContestLobby_EventScript_HavePokeblockCase:: @ 8155526
	msgbox SlateportCity_ContestLobby_Text_PutPokeblocksInThere, MSGBOX_NPC
	end

SlateportCity_ContestLobby_EventScript_15552F:: @ 815552F
	lockall
	fadescreen FADE_TO_BLACK
	showcontestwinner 3
	releaseall
	end

SlateportCity_ContestLobby_EventScript_Boy:: @ 8155536
	msgbox SlateportCity_ContestLobby_Text_LetsGetBlendingAlready, MSGBOX_NPC
	end

@ 815553F
	lockall
	special ShowBerryBlenderRecordWindow
	waitbuttonpress
	erasebox 0, 0, 29, 19
	releaseall
	end
