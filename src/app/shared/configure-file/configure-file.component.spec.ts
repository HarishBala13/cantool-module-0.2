import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ConfigureFileComponent } from './configure-file.component';

describe('ConfigureFileComponent', () => {
  let component: ConfigureFileComponent;
  let fixture: ComponentFixture<ConfigureFileComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [ConfigureFileComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ConfigureFileComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
