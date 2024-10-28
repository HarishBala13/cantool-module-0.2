import { CommonModule } from '@angular/common';
import { Component, inject, Input, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-signal-details',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './signal-details.component.html',
  styleUrl: './signal-details.component.css'
})
export class SignalDetailsComponent implements OnInit{

private route = inject(ActivatedRoute);

  signalID: string | null = null;
  currentDate: Date = new Date(); 
  // @Input() signal: string | null = null;
  
  ngOnInit(): void {
    this.route.paramMap.subscribe(params => {
      this.signalID = params.get('id');
    })    
  }
}
