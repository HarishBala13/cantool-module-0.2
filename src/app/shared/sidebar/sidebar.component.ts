import { CommonModule } from '@angular/common';
import { ChangeDetectorRef, Component, EventEmitter, inject, Output } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';

@Component({
  selector: 'app-sidebar',
  standalone: true,
  imports: [FormsModule, CommonModule],
  templateUrl: './sidebar.component.html',
  styleUrl: './sidebar.component.css'
})

export class SidebarComponent {

  // isFormDropdownOpen = false;
  // selectedForm: string | null = null;

  // private cdr = inject(ChangeDetectorRef);

  // toggleDropdown() {
  //   this.isFormDropdownOpen = true;
  //   this.cdr.detectChanges();
  //   console.log('hii');

  // }

  // showForm(form: string) {
  //   this.selectedForm = form;
  //   this.closeDropdown();
  // }

  // closeDropdown() {
  //   this.isFormDropdownOpen = false;
  // }

  private router = inject(Router);

  @Output() selectSignal = new EventEmitter<string>();

  networkOpen = false;
  bcmOpen = false;
  vbcOpen = false;

  toggleNetwork() {
    this.networkOpen = !this.networkOpen;
  }

  toggleBCM() {
    this.bcmOpen = !this.bcmOpen;
  }

  toggleVBC() {
    this.vbcOpen = !this.vbcOpen;
  }

  // emitSignal(signal: string) {
  //   this.selectSignal.emit(signal);
  // }

  selectSignalHandler(signal: string, event: Event) {
    event.stopPropagation();
    this.router.navigate(['/signal', signal]);
    // this.emitSignal(signal);
  }
}
