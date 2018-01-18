#include "global.h"
#include "battle_anim_81258BC.h"
#include "battle.h"
#include "battle_message.h"
#include "data2.h"
#include "link.h"
#include "main.h"
#include "menu_cursor.h"
#include "palette.h"
#include "rom3.h"
#include "constants/songs.h"
#include "sound.h"
#include "text.h"
#include "util.h"
#include "ewram.h"

extern struct Window gUnknown_03004210;
extern u8 gDisplayedStringBattle[];
extern u8 gActionSelectionCursor[];

extern const u8 BattleText_PlayerMenu[];
extern u8 gActiveBank;
extern const u8 BattleText_MenuOptionsSafari[];

extern void *gBattleBankFunc[];
extern u16 gBattle_BG0_Y;
extern u16 gBattle_BG0_X;
extern u8 gBattleBufferA[][0x200];
extern bool8 gDoingBattleAnim;
extern u8 gObjectBankIDs[];
extern struct SpriteTemplate gUnknown_02024E8C;
extern u16 gBattleTypeFlags;
extern u32 gBattleExecBuffer;
extern u16 gSpecialVar_ItemId;
extern MainCallback gPreBattleCallback1;
extern u8 gBankInMenu;
extern u8 gHealthboxIDs[];
extern u16 gBattlePartyID[];
extern u16 gUnknown_02024DE8;
extern u8 gBattleOutcome;

extern u8 GetBankSide(u8);
extern u8 GetBankByIdentity(u8);
extern u8 GetBankIdentity(u8);
extern void LoadPlayerTrainerBankSprite();
extern u8 sub_8079E90();
extern void sub_80313A0(struct Sprite *);
extern void sub_810BADC(void);
extern void sub_8045A5C();
extern void StartBattleIntroAnim();
extern void sub_804777C();
extern void sub_8043DFC();
extern bool8 move_anim_start_t3();

#if ENGLISH
#define SUB_812BB10_TILE_DATA_OFFSET 440
#elif GERMAN
#define SUB_812BB10_TILE_DATA_OFFSET 444
#endif

// this file's functions
void SafariHandleGetAttributes(void);
void SafariHandlecmd1(void);
void SafariHandleSetAttributes(void);
void SafariHandlecmd3(void);
void SafariHandleLoadPokeSprite(void);
void SafariHandleSendOutPoke(void);
void SafariHandleReturnPokeToBall(void);
void SafariHandleTrainerThrow(void);
void SafariHandleTrainerSlide(void);
void SafariHandleTrainerSlideBack(void);
void SafariHandlecmd10(void);
void SafariHandlecmd11(void);
void SafariHandlecmd12(void);
void SafariHandleBallThrow(void);
void SafariHandlePuase(void);
void SafariHandleMoveAnimation(void);
void SafariHandlePrintString(void);
void SafariHandlePrintStringPlayerOnly(void);
void SafariHandlecmd18(void);
void SafariHandlecmd19(void);
void SafariHandlecmd20(void);
void SafariHandleOpenBag(void);
void SafariHandlecmd22(void);
void SafariHandlecmd23(void);
void SafariHandleHealthBarUpdate(void);
void SafariHandleExpBarUpdate(void);
void SafariHandleStatusIconUpdate(void);
void SafariHandleStatusAnimation(void);
void SafariHandleStatusXor(void);
void SafariHandlecmd29(void);
void SafariHandleDMATransfer(void);
void SafariHandlecmd31(void);
void SafariHandlecmd32(void);
void SafariHandlecmd33(void);
void SafariHandlecmd34(void);
void SafariHandlecmd35(void);
void SafariHandlecmd36(void);
void SafariHandlecmd37(void);
void SafariHandlecmd38(void);
void SafariHandlecmd39(void);
void SafariHandlecmd40(void);
void SafariHandleHitAnimation(void);
void SafariHandlecmd42(void);
void SafariHandleEffectivenessSound(void);
void SafariHandlecmd44(void);
void SafariHandleFaintingCry(void);
void SafariHandleIntroSlide(void);
void SafariHandleTrainerBallThrow(void);
void SafariHandlecmd48(void);
void SafariHandlecmd49(void);
void SafariHandlecmd50(void);
void SafariHandleSpriteInvisibility(void);
void SafariHandleBattleAnimation(void);
void SafariHandleLinkStandbyMsg(void);
void SafariHandleResetActionMoveSelection(void);
void SafariHandlecmd55(void);
void SafariHandlecmd56(void);

// const data
typedef void (*BattleBufferCmd) (void);
const BattleBufferCmd gSafariBufferCommands[] =
{
    SafariHandleGetAttributes,
    SafariHandlecmd1,
    SafariHandleSetAttributes,
    SafariHandlecmd3,
    SafariHandleLoadPokeSprite,
    SafariHandleSendOutPoke,
    SafariHandleReturnPokeToBall,
    SafariHandleTrainerThrow,
    SafariHandleTrainerSlide,
    SafariHandleTrainerSlideBack,
    SafariHandlecmd10,
    SafariHandlecmd11,
    SafariHandlecmd12,
    SafariHandleBallThrow,
    SafariHandlePuase,
    SafariHandleMoveAnimation,
    SafariHandlePrintString,
    SafariHandlePrintStringPlayerOnly,
    SafariHandlecmd18,
    SafariHandlecmd19,
    SafariHandlecmd20,
    SafariHandleOpenBag,
    SafariHandlecmd22,
    SafariHandlecmd23,
    SafariHandleHealthBarUpdate,
    SafariHandleExpBarUpdate,
    SafariHandleStatusIconUpdate,
    SafariHandleStatusAnimation,
    SafariHandleStatusXor,
    SafariHandlecmd29,
    SafariHandleDMATransfer,
    SafariHandlecmd31,
    SafariHandlecmd32,
    SafariHandlecmd33,
    SafariHandlecmd34,
    SafariHandlecmd35,
    SafariHandlecmd36,
    SafariHandlecmd37,
    SafariHandlecmd38,
    SafariHandlecmd39,
    SafariHandlecmd40,
    SafariHandleHitAnimation,
    SafariHandlecmd42,
    SafariHandleEffectivenessSound,
    SafariHandlecmd44,
    SafariHandleFaintingCry,
    SafariHandleIntroSlide,
    SafariHandleTrainerBallThrow,
    SafariHandlecmd48,
    SafariHandlecmd49,
    SafariHandlecmd50,
    SafariHandleSpriteInvisibility,
    SafariHandleBattleAnimation,
    SafariHandleLinkStandbyMsg,
    SafariHandleResetActionMoveSelection,
    SafariHandlecmd55,
    SafariHandlecmd56,
};
// code

void SafariBufferExecCompleted(void);
void bx_wait_t6(void);
void sub_812B65C(void);
void SafariBufferRunCommand(void);
void sub_812B758(void);

void unref_sub_812B464(void)
{
}

void SetBankFuncToSafariBufferRunCommand(void)
{
    gBattleBankFunc[gActiveBank] = SafariBufferRunCommand;
}

void SafariBufferRunCommand(void)
{
    if (gBattleExecBuffer & gBitTable[gActiveBank])
    {
        if (gBattleBufferA[gActiveBank][0] < 0x39)
            gSafariBufferCommands[gBattleBufferA[gActiveBank][0]]();
        else
            SafariBufferExecCompleted();
    }
}

#if DEBUG
__attribute__((naked))
void bx_battle_menu_t6_2(void)
{
    asm("\
	push	{r4, r5, lr}\n\
	add	sp, sp, #0xfffffffc\n\
	ldr	r0, ._94\n\
	ldrh	r1, [r0, #0x2e]\n\
	mov	r2, #0x1\n\
	add	r0, r2, #0\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._89	@cond_branch\n\
	mov	r0, #0x5\n\
	bl	PlaySE\n\
	bl	DestroyMenuCursor\n\
	ldr	r1, ._94 + 4\n\
	ldr	r0, ._94 + 8\n\
	ldrb	r0, [r0]\n\
	add	r0, r0, r1\n\
	ldrb	r0, [r0]\n\
	cmp	r0, #0x1\n\
	beq	._90	@cond_branch\n\
	cmp	r0, #0x1\n\
	bgt	._91	@cond_branch\n\
	cmp	r0, #0\n\
	beq	._92	@cond_branch\n\
	b	._101\n\
._95:\n\
	.align	2, 0\n\
._94:\n\
	.word	gMain\n\
	.word	gActionSelectionCursor\n\
	.word	gActiveBank\n\
._91:\n\
	cmp	r0, #0x2\n\
	beq	._96	@cond_branch\n\
	cmp	r0, #0x3\n\
	beq	._97	@cond_branch\n\
	b	._101\n\
._92:\n\
	mov	r0, #0x1\n\
	mov	r1, #0x5\n\
	b	._100\n\
._90:\n\
	mov	r0, #0x1\n\
	mov	r1, #0x6\n\
	b	._100\n\
._96:\n\
	mov	r0, #0x1\n\
	mov	r1, #0x7\n\
._100:\n\
	mov	r2, #0x0\n\
	bl	Emitcmd33\n\
	b	._101\n\
._97:\n\
	mov	r0, #0x1\n\
	mov	r1, #0x8\n\
	mov	r2, #0x0\n\
	bl	Emitcmd33\n\
._101:\n\
	bl	SafariBufferExecCompleted\n\
	b	._129\n\
._89:\n\
	mov	r3, #0x20\n\
	add	r0, r3, #0\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._103	@cond_branch\n\
	ldr	r5, ._107\n\
	ldr	r4, ._107 + 4\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r1, [r0]\n\
	add	r0, r2, #0\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	bne	._104	@cond_branch\n\
	b	._129\n\
._104:\n\
	mov	r0, #0x5\n\
	bl	PlaySE\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r0, [r0]\n\
	bl	nullsub_8\n\
	ldrb	r1, [r4]\n\
	add	r1, r1, r5\n\
	ldrb	r0, [r1]\n\
	mov	r2, #0x1\n\
	b	._111\n\
._108:\n\
	.align	2, 0\n\
._107:\n\
	.word	gActionSelectionCursor\n\
	.word	gActiveBank\n\
._103:\n\
	mov	r0, #0x10\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._109	@cond_branch\n\
	ldr	r5, ._112\n\
	ldr	r4, ._112 + 4\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r1, [r0]\n\
	add	r0, r2, #0\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	bne	._129	@cond_branch\n\
	mov	r0, #0x5\n\
	bl	PlaySE\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r0, [r0]\n\
	bl	nullsub_8\n\
	ldrb	r1, [r4]\n\
	add	r1, r1, r5\n\
	ldrb	r0, [r1]\n\
	mov	r2, #0x1\n\
	b	._111\n\
._113:\n\
	.align	2, 0\n\
._112:\n\
	.word	gActionSelectionCursor\n\
	.word	gActiveBank\n\
._109:\n\
	mov	r0, #0x40\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._114	@cond_branch\n\
	ldr	r5, ._117\n\
	ldr	r4, ._117 + 4\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r1, [r0]\n\
	mov	r0, #0x2\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._129	@cond_branch\n\
	b	._116\n\
._118:\n\
	.align	2, 0\n\
._117:\n\
	.word	gActionSelectionCursor\n\
	.word	gActiveBank\n\
._114:\n\
	mov	r0, #0x80\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._119	@cond_branch\n\
	ldr	r5, ._122\n\
	ldr	r4, ._122 + 4\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r1, [r0]\n\
	mov	r0, #0x2\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	bne	._129	@cond_branch\n\
._116:\n\
	mov	r0, #0x5\n\
	bl	PlaySE\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r0, [r0]\n\
	bl	nullsub_8\n\
	ldrb	r1, [r4]\n\
	add	r1, r1, r5\n\
	ldrb	r0, [r1]\n\
	mov	r2, #0x2\n\
._111:\n\
	eor	r0, r0, r2\n\
	strb	r0, [r1]\n\
	ldrb	r0, [r4]\n\
	add	r0, r0, r5\n\
	ldrb	r0, [r0]\n\
	mov	r1, #0x0\n\
	bl	sub_802E3E4\n\
	b	._129\n\
._123:\n\
	.align	2, 0\n\
._122:\n\
	.word	gActionSelectionCursor\n\
	.word	gActiveBank\n\
._119:\n\
	mov	r0, #0x80\n\
	lsl	r0, r0, #0x1\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._124	@cond_branch\n\
	ldr	r0, ._127\n\
	ldrb	r2, [r0]\n\
	lsl	r0, r2, #0x1\n\
	add	r0, r0, r2\n\
	lsl	r0, r0, #0x2\n\
	ldr	r1, ._127 + 4\n\
	add	r0, r0, r1\n\
	ldrb	r1, [r0]\n\
	add	r0, r3, #0\n\
	and	r0, r0, r1\n\
	lsl	r0, r0, #0x18\n\
	lsr	r0, r0, #0x18\n\
	cmp	r0, #0\n\
	bne	._129	@cond_branch\n\
	str	r0, [sp]\n\
	add	r0, r2, #0\n\
	add	r1, r2, #0\n\
	mov	r3, #0x4\n\
	bl	move_anim_start_t3\n\
	b	._129\n\
._128:\n\
	.align	2, 0\n\
._127:\n\
	.word	gActiveBank\n\
	.word	+0x2017810\n\
._124:\n\
	mov	r0, #0x8\n\
	and	r0, r0, r1\n\
	cmp	r0, #0\n\
	beq	._129	@cond_branch\n\
	bl	sub_804454C\n\
._129:\n\
	add	sp, sp, #0x4\n\
	pop	{r4, r5}\n\
	pop	{r0}\n\
	bx	r0");
}
#else
void bx_battle_menu_t6_2(void)
{
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        DestroyMenuCursor();

        // Useless switch statement.
        switch (gActionSelectionCursor[gActiveBank])
        {
        case 0:
            Emitcmd33(1, 5, 0);
            break;
        case 1:
            Emitcmd33(1, 6, 0);
            break;
        case 2:
            Emitcmd33(1, 7, 0);
            break;
        case 3:
            Emitcmd33(1, 8, 0);
            break;
        }
        SafariBufferExecCompleted();
    }
    else if (gMain.newKeys & DPAD_LEFT)
    {
        if (gActionSelectionCursor[gActiveBank] & 1)
        {
            PlaySE(SE_SELECT);
            nullsub_8(gActionSelectionCursor[gActiveBank]);
            gActionSelectionCursor[gActiveBank] ^= 1;
            sub_802E3E4(gActionSelectionCursor[gActiveBank], 0);
        }
    }
    else if (gMain.newKeys & DPAD_RIGHT)
    {
        if (!(gActionSelectionCursor[gActiveBank] & 1))
        {
            PlaySE(SE_SELECT);
            nullsub_8(gActionSelectionCursor[gActiveBank]);
            gActionSelectionCursor[gActiveBank] ^= 1;
            sub_802E3E4(gActionSelectionCursor[gActiveBank], 0);
        }
    }
    else if (gMain.newKeys & DPAD_UP)
    {
        if (gActionSelectionCursor[gActiveBank] & 2)
        {
            PlaySE(SE_SELECT);
            nullsub_8(gActionSelectionCursor[gActiveBank]);
            gActionSelectionCursor[gActiveBank] ^= 2;
            sub_802E3E4(gActionSelectionCursor[gActiveBank], 0);
        }
    }
    else if (gMain.newKeys & DPAD_DOWN)
    {
        if (!(gActionSelectionCursor[gActiveBank] & 2))
        {
            PlaySE(SE_SELECT);
            nullsub_8(gActionSelectionCursor[gActiveBank]);
            gActionSelectionCursor[gActiveBank] ^= 2;
            sub_802E3E4(gActionSelectionCursor[gActiveBank], 0);
        }
    }
}
#endif

void sub_812B65C(void)
{
    if (gSprites[gObjectBankIDs[gActiveBank]].callback == SpriteCallbackDummy)
        SafariBufferExecCompleted();
}

void sub_812B694(void)
{
    if (gUnknown_03004210.state == 0)
        SafariBufferExecCompleted();
}

void sub_812B6AC(void)
{
    if (!gPaletteFade.active)
    {
        gMain.inBattle = FALSE;
        gMain.callback1 = gPreBattleCallback1;
        SetMainCallback2(gMain.savedCallback);
    }
}

void bx_wait_t6(void)
{
    if (!gDoingBattleAnim || !ewram17810[gActiveBank].unk0_6)
        SafariBufferExecCompleted();
}

void sub_812B724(void)
{
    if (!gPaletteFade.active)
    {
        gBattleBankFunc[gActiveBank] = sub_812B758;
        sub_810BADC();
    }
}

void sub_812B758(void)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        Emitcmd35(1, gSpecialVar_ItemId);
        SafariBufferExecCompleted();
    }
}

void sub_812B794(void)
{
    if (!ewram17810[gActiveBank].unk0_5)
        SafariBufferExecCompleted();
}

void SafariBufferExecCompleted(void)
{
    gBattleBankFunc[gActiveBank] = SafariBufferRunCommand;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        u8 playerId = GetMultiplayerId();

        PrepareBufferDataTransferLink(2, 4, &playerId);
        gBattleBufferA[gActiveBank][0] = 0x38;
    }
    else
    {
        gBattleExecBuffer &= ~gBitTable[gActiveBank];
    }
}

void unref_sub_812B838(void)
{
    if (!ewram17810[gActiveBank].unk0_4)
        SafariBufferExecCompleted();
}

void SafariHandleGetAttributes(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd1(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleSetAttributes(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd3(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleLoadPokeSprite(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleSendOutPoke(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleReturnPokeToBall(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleTrainerThrow(void)
{
    LoadPlayerTrainerBankSprite(gSaveBlock2.playerGender, gActiveBank);
    GetMonSpriteTemplate_803C5A0(gSaveBlock2.playerGender, GetBankIdentity(gActiveBank));
    gObjectBankIDs[gActiveBank] = CreateSprite(
      &gUnknown_02024E8C,
      80,
      (8 - gTrainerBackPicCoords[gSaveBlock2.playerGender].coords) * 4 + 80,
      30);
    gSprites[gObjectBankIDs[gActiveBank]].oam.paletteNum = gActiveBank;
    gSprites[gObjectBankIDs[gActiveBank]].pos2.x = 240;
    gSprites[gObjectBankIDs[gActiveBank]].data[0] = -2;
    gSprites[gObjectBankIDs[gActiveBank]].callback = sub_80313A0;
    gBattleBankFunc[gActiveBank] = sub_812B65C;
}

void SafariHandleTrainerSlide(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleTrainerSlideBack(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd10(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd11(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd12(void)
{
    ewram17840.unk8 = 4;
    gDoingBattleAnim = 1;
    move_anim_start_t4(gActiveBank, gActiveBank, GetBankByIdentity(1), 4);
    gBattleBankFunc[gActiveBank] = bx_wait_t6;
}

void SafariHandleBallThrow(void)
{
    u8 var = gBattleBufferA[gActiveBank][1];

    ewram17840.unk8 = var;
    gDoingBattleAnim = 1;
    move_anim_start_t4(gActiveBank, gActiveBank, GetBankByIdentity(1), 4);
    gBattleBankFunc[gActiveBank] = bx_wait_t6;
}

// TODO: spell Pause correctly
void SafariHandlePuase(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleMoveAnimation(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlePrintString(void)
{
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    BufferStringBattle(*(u16 *)&gBattleBufferA[gActiveBank][2]);
    Text_InitWindow8002EB0(&gUnknown_03004210, gDisplayedStringBattle, 144, 2, 15);
    gBattleBankFunc[gActiveBank] = sub_812B694;
}

void SafariHandlePrintStringPlayerOnly(void)
{
    if (GetBankSide(gActiveBank) == 0)
        SafariHandlePrintString();
    else
        SafariBufferExecCompleted();
}

void SafariHandlecmd18(void)
{
    int i;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 160;
    gUnknown_03004210.paletteNum = 0;
    Text_FillWindowRectDefPalette(&gUnknown_03004210, 10, 2, 15, 27, 18);
    Text_FillWindowRectDefPalette(&gUnknown_03004210, 10, 2, 35, 16, 36);
    gBattleBankFunc[gActiveBank] = bx_battle_menu_t6_2;

    Text_InitWindow(&gUnknown_03004210, BattleText_MenuOptionsSafari, 400, 18, 35);
    Text_PrintWindow8002F44(&gUnknown_03004210);
    MenuCursor_Create814A5C0(0, 0xFFFF, 12, 11679, 0);

    for (i = 0; i < 4; i++)
        nullsub_8(i);

    sub_802E3E4(gActionSelectionCursor[gActiveBank], 0);
    StrCpyDecodeToDisplayedStringBattle(BattleText_PlayerMenu);

    Text_InitWindow(&gUnknown_03004210, gDisplayedStringBattle, SUB_812BB10_TILE_DATA_OFFSET, 2, 35);
    Text_PrintWindow8002F44(&gUnknown_03004210);
}

void SafariHandlecmd19(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd20(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleOpenBag(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
    gBattleBankFunc[gActiveBank] = sub_812B724;
    gBankInMenu = gActiveBank;
}

void SafariHandlecmd22(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd23(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleHealthBarUpdate(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleExpBarUpdate(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleStatusIconUpdate(void)
{
    sub_8045A5C(gHealthboxIDs[gActiveBank], &gPlayerParty[gBattlePartyID[gActiveBank]], 11);
    SafariBufferExecCompleted();
}

void SafariHandleStatusAnimation(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleStatusXor(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd29(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleDMATransfer(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd31(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd32(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd33(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd34(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd35(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd36(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd37(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd38(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd39(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd40(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleHitAnimation(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd42(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleEffectivenessSound(void)
{
    s8 pan;

    if (GetBankSide(gActiveBank) == 0)
        pan = -64;
    else
        pan = 63;
    PlaySE12WithPanning(gBattleBufferA[gActiveBank][1] | (gBattleBufferA[gActiveBank][2] << 8), pan);
    SafariBufferExecCompleted();
}

void SafariHandlecmd44(void)
{
    PlayFanfare(gBattleBufferA[gActiveBank][1] | (gBattleBufferA[gActiveBank][2] << 8));
    SafariBufferExecCompleted();
}

void SafariHandleFaintingCry(void)
{
    u16 species = GetMonData(&gPlayerParty[gBattlePartyID[gActiveBank]], MON_DATA_SPECIES);

    PlayCry1(species, 25);
    SafariBufferExecCompleted();
}

void SafariHandleIntroSlide(void)
{
    StartBattleIntroAnim(gBattleBufferA[gActiveBank][1]);
    gUnknown_02024DE8 |= 1;
    SafariBufferExecCompleted();
}

void SafariHandleTrainerBallThrow(void)
{
    sub_8045A5C(gHealthboxIDs[gActiveBank], &gPlayerParty[gBattlePartyID[gActiveBank]], 10);
    sub_804777C(gActiveBank);
    sub_8043DFC(gHealthboxIDs[gActiveBank]);
    SafariBufferExecCompleted();
}

void SafariHandlecmd48(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd49(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd50(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleSpriteInvisibility(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleBattleAnimation(void)
{
    u8 r3 = gBattleBufferA[gActiveBank][1];
    u16 r4 = gBattleBufferA[gActiveBank][2] | (gBattleBufferA[gActiveBank][3] << 8);

    if (move_anim_start_t3(gActiveBank, gActiveBank, gActiveBank, r3, r4) != 0)
        SafariBufferExecCompleted();
    else
        gBattleBankFunc[gActiveBank] = sub_812B794;
}

void SafariHandleLinkStandbyMsg(void)
{
    SafariBufferExecCompleted();
}

void SafariHandleResetActionMoveSelection(void)
{
    SafariBufferExecCompleted();
}

void SafariHandlecmd55(void)
{
    gBattleOutcome = gBattleBufferA[gActiveBank][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    SafariBufferExecCompleted();
    if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && !(gBattleTypeFlags & BATTLE_TYPE_WILD))
        gBattleBankFunc[gActiveBank] = sub_812B6AC;
}

void SafariHandlecmd56(void)
{
}
