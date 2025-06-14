FallarborTown_ContestLobby_MapScripts:: @ 81539C1
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_ContestLobby_OnTransition
	.byte 0

FallarborTown_ContestLobby_OnTransition:: @ 81539C7
	call LilycoveCity_ContestLobby_EventScript_TryShowContestReporter
	end

FallarborTown_ContestLobby_EventScript_ContestReceptionist:: @ 81539CD
	setvar VAR_0x800B, 6
	setvar VAR_CONTEST_RANK, 1
	call LilycoveCity_ContestLobby_EventScript_1A4E92
	call FallarborTown_ContestLobby_EventScript_1539F8
	special SetContestTrainerGfxIds
	call LilycoveCity_ContestLobby_EventScript_SetupRivalGfxId
	setvar VAR_CONTEST_LOCATION, 2
	warp MAP_LINK_CONTEST_ROOM1, 255, 7, 5
	waitstate
	end

FallarborTown_ContestLobby_EventScript_1539F8:: @ 81539F8
	lockall
	applymovement 1, FallarborTown_ContestLobby_Movement_153A7C
	waitmovement 0
	playse SE_BRIDGE_WALK
	setmetatile 4, 2, METATILE_Contest_WallShadow, 1
	setmetatile 4, 3, METATILE_Contest_FloorShadow, 1
	special DrawWholeMapView
	applymovement 1, FallarborTown_ContestLobby_Movement_153A7F
	waitmovement 0
	playse SE_BRIDGE_WALK
	setmetatile 4, 2, METATILE_Contest_CounterFlap_Top, 1
	setmetatile 4, 3, METATILE_Contest_CounterFlap_Bottom, 1
	special DrawWholeMapView
	delay 20
	applymovement 1, FallarborTown_ContestLobby_Movement_153A8C
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_ContestLobby_Movement_153A7A
	waitmovement 0
	msgbox LilycoveCity_ContestLobby_Text_ComeThroughHere, MSGBOX_DEFAULT
	closemessage
	applymovement 1, FallarborTown_ContestLobby_Movement_153A83
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_ContestLobby_Movement_153A70
	waitmovement 0
	releaseall
	return

FallarborTown_ContestLobby_Movement_153A70:: @ 8153A70
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

FallarborTown_ContestLobby_Movement_153A7A:: @ 8153A7A
	walk_in_place_fastest_left
	step_end

FallarborTown_ContestLobby_Movement_153A7C:: @ 8153A7C
	walk_left
	walk_in_place_fastest_down
	step_end

FallarborTown_ContestLobby_Movement_153A7F:: @ 8153A7F
	walk_down
	walk_down
	walk_in_place_fastest_up
	step_end

FallarborTown_ContestLobby_Movement_153A83:: @ 8153A83
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

FallarborTown_ContestLobby_Movement_153A8C:: @ 8153A8C
	walk_in_place_fastest_right
	step_end

FallarborTown_ContestLobby_EventScript_Boy:: @ 8153A8E
	msgbox FallarborTown_ContestLobby_Text_UsedToHaveSketch, MSGBOX_NPC
	end

FallarborTown_ContestLobby_EventScript_SketchArtist:: @ 8153A97
	goto_if_set FLAG_CONTEST_SKETCH_CREATED, FallarborTown_ContestLobby_EventScript_153AA9
	msgbox FallarborTown_ContestLobby_Text_ICreateSketches, MSGBOX_NPC
	end

FallarborTown_ContestLobby_EventScript_153AA9:: @ 8153AA9
	msgbox FallarborTown_ContestLobby_Text_YourSketchIsUp, MSGBOX_NPC
	end

FallarborTown_ContestLobby_EventScript_Lass:: @ 8153AB2
	msgbox FallarborTown_ContestLobby_Text_AreYouMakingPokeblock, MSGBOX_NPC
	end

FallarborTown_ContestLobby_EventScript_ContestWinner1:: @ 8153ABB
	lockall
	fadescreen FADE_TO_BLACK
	showcontestwinner 2
	releaseall
	end

FallarborTown_ContestLobby_EventScript_ContestWinner2:: @ 8153AC2
	lockall
	special ShowBerryBlenderRecordWindow
	waitbuttonpress
	erasebox 0, 0, 29, 19
	releaseall
	end
