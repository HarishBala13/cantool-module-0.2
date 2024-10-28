import { ChangeDetectorRef, Component, inject } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-configure-file',
  standalone: true,
  imports: [FormsModule, ReactiveFormsModule, CommonModule],
  templateUrl: './configure-file.component.html',
  styleUrl: './configure-file.component.css'
})

export class ConfigureFileComponent {

  private cdr = inject(ChangeDetectorRef);

  txCount: number = 0;
  rxCount: number = 0;
  showAdditionalFields: boolean = false;
  saveButtonDisabled: boolean = false;

  txFieldArray: number[] = [];
  rxFieldArray: number[] = [];
  txFields: { messageName: string; startBit: string; length: string }[] = [];
  rxFields: { messageName: string; startBit: string; length: string }[] = [];

  bitrate: string = '';
  channel: string = '';

  updateTxFields() {
    this.txFieldArray = Array(this.txCount).fill(0);
    this.txFields = Array.from({ length: this.txCount }, () => ({ messageName: '', startBit: '', length: '' }));
  }

  updateRxFields() {
    this.rxFieldArray = Array(this.rxCount).fill(0);
    this.rxFields = Array.from({ length: this.rxCount }, () => ({ messageName: '', startBit: '', length: '' }));
  }

  save() {
    if (this.txCount > 0 && this.rxCount > 0) {
      this.showAdditionalFields = true;
      this.saveButtonDisabled = true;
      this.cdr.detectChanges();
      setTimeout(() => {
        // const additionalFields = document.querySelector('.additional-fields');
        const additionalFields = document.querySelector('.additional-fields') as HTMLElement; // Type assertion here
        if (additionalFields) {
          additionalFields.style.opacity = '1';
          additionalFields.style.filter = 'blur(0)';
        }
      }, 0);
    }
  }

  cancel() {
    // Logic for canceling the form submission (if any)
  }
  edit() {

  }
  configure() {

  }
}
// export class ConfigureFileComponent {

//   isConfigureFileVisible: boolean = false;

//   txArray: string[] = [];
//   rxArray: string[] = [];
//   code: string = '';

//   messageCountForm!: FormGroup;
//   confirgurationForm!: FormGroup;

//   private electronService = inject(ElectronService);
//   private cdr = inject(ChangeDetectorRef);
//   private formBuilder = inject(FormBuilder);

//   ngOnInit(): void {
//     this.electronService.on('open-form', () => {
//       this.isConfigureFileVisible = true;
//       this.cdr.detectChanges();
//       this.electronService.on('inspect-element', () => { })
//     });
//   }

//   constructor() {
//     this.messageCountForm = this.formBuilder.group({
//       txMessageCount: ['', Validators.required],
//       rxMessageCount: ['', Validators.required]
//     })
//   }

//   messageCountFormSubmit() {
//     if (this.messageCountForm.valid) {
//       console.log('Value got from user', this.messageCountForm.value);
//     }
//     console.log('else Value got from user', this.messageCountForm.value);
//   }

//   submitCode() {
//     this.electronService.send('save-code', this.code);
//   }
// }