import { ChangeDetectorRef, Component, EventEmitter, inject, Input, Output } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';
import { ElectronService } from '../../services/electron.service';
import { FooterComponent } from "../footer/footer.component";

interface Signal {
  startBit: number;
  length: number;
  message: string;
}

@Component({
  selector: 'app-configure-file',
  standalone: true,
  imports: [FormsModule, ReactiveFormsModule, CommonModule, FooterComponent],
  templateUrl: './configure-file.component.html',
  styleUrl: './configure-file.component.css'
})

export class ConfigureFileComponent {

  private cdr = inject(ChangeDetectorRef);
  private electronService = inject(ElectronService);

  @Input() isConfigureFileVisible: boolean = false;
  @Output() closeConfigureFile = new EventEmitter<void>();

  txCount: number = 0;
  rxCount: number = 0;
  msgASigCount: number = 0;
  msgBSigCount: number = 0;

  bitrate: string = '';
  channel: string = '';
  fileName: string = '';
  configContent: string = '';

  showAdditionalFields: boolean = false;
  saveButtonDisabled: boolean = false;

  msgASignals: Signal[] = [];
  msgBSignals: Signal[] = [];
  configureArray: string[] = [];

  txFieldArray = [{ messageName: '', start_bit: 0, length: 4 }];
  rxFieldArray = [{ messageName: '', start_bit: 0, length: 4 }];
  txFields: { messageName: string; startBit: string; length: string }[] = [];
  rxFields: { messageName: string; startBit: string; length: string }[] = [];

  generateConfig() {
    this.msgASignals = this.txFieldArray.map(field => ({
      startBit: field.start_bit,
      length: field.length,
      message: field.messageName
    }));

    this.msgBSignals = this.rxFieldArray.map(field => ({
      startBit: field.start_bit,
      length: field.length,
      message: field.messageName
    }));

    this.configContent = `
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Ielektron Technologies Pvt Ltd.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Ielektron Technologies Pvt Ltd.
 *                Ielektron Technologies Pvt Ltd grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Ielektron Technologies Pvt Ltd.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Can_UserCfg.c
 *        \brief  CAN User configuration Source file.
 *
 *      \details  This file contains the declaration and initializationConfig variables
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/

#include "CAN_UserCfg.h"

/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS
*********************************************************************************************************************/

#define MSGA_SIG_COUNT ${this.txCount}
#define MSGB_SIG_COUNT ${this.rxCount}

/**********************************************************************************************************************
*  GLOBAL DATA
**********************************************************************************************************************/
Com_SigInfo_t MsgA_SigDef[MSGA_SIG_COUNT] = {
  ${this.msgASignals.map(sig => `{ /*start_bit*/ ${sig.startBit},  /*len*/ ${sig.length}, /*msg*/ ${sig.message} }`).join(',\n  ')}
};

Com_SigInfo_t MsgB_SigDef[MSGB_SIG_COUNT] = {
  ${this.msgBSignals.map(sig => `{ /*start_bit*/ ${sig.startBit},  /*len*/ ${sig.length}, /*msg*/ ${sig.message} }`).join(',\n  ')}
};

Com_MessageInfo_t Com_TxMessageInfo_Table[CAN_TXMESSAGE_MAX] = {
    { /*siginfo*/ MsgA_SigDef, /*sig_count*/ MSGA_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x30, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ MsgB_SigDef, /*sig_count*/ MSGB_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x31, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x32, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x33, /*len*/ CAN_STD_FRAME_SIZE} }
};

Com_MessageInfo_t Com_RxMessageInfo_Table[CAN_RXMESSAGE_MAX] = {
    { /*siginfo*/ MsgA_SigDef, /*sig_count*/ MSGA_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x200, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ MsgB_SigDef, /*sig_count*/ MSGB_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x400, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x410, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x420, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x500, /*len*/ CAN_STD_FRAME_SIZE} }
};

/**********************************************************************************************************************
*  END OF FILE: Can_UserCfg.c
*********************************************************************************************************************/
`;
  }

  getStartBit(array: any[], index: number): number {
    if (index === 0) {
      return array[0].start_bit;
    }
    return array[index - 1].start_bit + array[index - 1].length;
  }

  updateStartBit(array: any[], index: number): void {
    for (let i = index + 1; i < array.length; i++) {
      array[i] = { ...array[i], start_bit: this.getStartBit(array, i) };
    }
  }

  updateTxFields() {
    this.txFieldArray = Array.from({ length: this.txCount }, () => ({ messageName: '', start_bit: 0, length: 4 }));
    this.txFields = Array.from({ length: this.txCount }, () => ({ messageName: '', startBit: '', length: '' }));
  }

  updateRxFields() {
    this.rxFieldArray = Array.from({ length: this.rxCount }, () => ({ messageName: '', start_bit: 0, length: 4 }));
    this.rxFields = Array.from({ length: this.rxCount }, () => ({ messageName: '', startBit: '', length: '' }));
  }

  save() {
    if (this.txCount > 0 && this.rxCount > 0) {
      this.showAdditionalFields = true;
      this.saveButtonDisabled = true;
      this.cdr.detectChanges();
    }
  }

  cancel() {
      this.showAdditionalFields = false;
      this.saveButtonDisabled = false;
      this.cdr.detectChanges();
  }

  close() {
    this.closeConfigureFile.emit();
    this.cdr.detectChanges();
  }

  edit() { }

  configure() {
    this.generateConfig();
    this.configureArray.push(this.configContent, this.fileName);
    this.electronService.send('save-code', this.configureArray);
  }

}