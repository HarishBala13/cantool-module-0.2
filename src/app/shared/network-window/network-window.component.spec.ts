import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NetworkWindowComponent } from './network-window.component';

describe('NetworkWindowComponent', () => {
  let component: NetworkWindowComponent;
  let fixture: ComponentFixture<NetworkWindowComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [NetworkWindowComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(NetworkWindowComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
