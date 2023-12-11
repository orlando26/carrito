import { Component, OnInit, ViewChild } from '@angular/core';
import { IonModal } from '@ionic/angular';
import { OverlayEventDetail } from '@ionic/core/components';
// Import the wrapper class
import { BleClient } from '@capacitor-community/bluetooth-le';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-main',
  templateUrl: './main.page.html',
  styleUrls: ['./main.page.scss'],
})
export class MainPage implements OnInit {
  @ViewChild(IonModal) modal: IonModal;

  message = 'This modal example uses triggers to automatically open a modal when the button is clicked.';
  name: string = '';

  constructor(private http: HttpClient) { }


  async ngOnInit() {
    console.log('csdc');
    await BleClient.initialize();
  }

  up() {
    this.http.get('https://pokeapi.co/api/v2/pokemon/').subscribe(res => {
      console.log(res);
    });
  }

  getDevicesList() {
    BleClient.requestDevice({namePrefix: "HC-05"}).then();
  }

  cancel() {
    this.modal.dismiss(null, 'cancel');
  }

  confirm() {
    this.modal.dismiss(this.name, 'confirm');
  }

  onWillDismiss(event: Event) { 
    const ev = event as CustomEvent<OverlayEventDetail<string>>;
    if (ev.detail.role === 'confirm') {
      this.message = `Hello, ${ev.detail.data}!`;
    }
  }

}
