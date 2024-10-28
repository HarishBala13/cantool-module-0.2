import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SignalDetailsComponent } from './signal-details.component';

describe('SignalDetailsComponent', () => {
  let component: SignalDetailsComponent;
  let fixture: ComponentFixture<SignalDetailsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [SignalDetailsComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(SignalDetailsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
