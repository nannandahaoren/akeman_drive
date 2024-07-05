import { remap } from './Tool.js'

export class Joystick {
  constructor(options = {}) {
    this.maxSpeed = 300;
    var prevX = 0;
    var prevY = 0;
    var newX = 0;
    var newY = 0;

    const joystick = new VirtualJoystick({
      container: document.getElementById('container'),
      mouseSupport: true,
      limitStickTravel: true,
      stationaryBase: true,
      baseX: 120,
      baseY: (window.innerHeight + 70) / 2
    });

    const handleChange = (forceReset=false) => {
      newX = Math.round(joystick.deltaX());
      newY = Math.round(joystick.deltaY()) * -1;

      if(forceReset) {
        newX = 0;
        newY = 0;
      }

      if (newX != prevX || newY != prevY) {
        let angle = this.remapAngle(Math.abs(newX));
        angle *= newX > 0 ? 1 : -1;
        angle = Math.ceil(angle);

        let speed = this.remapSpeed(Math.abs(newY));
        speed *= newY > 0 ? 1 : -1;
        speed = +speed.toFixed(2);

        options.change && options.change( speed, angle);
      }
      prevX = newX;
      prevY = newY;
    }

    joystick.addEventListener('move', handleChange)
    joystick.addEventListener('touchEnd', ()=>{
      handleChange(true);
    })
  }

  remapAngle(value) {
    return remap(0, 100, 0, 90, value)
  }

  remapSpeed(value) {
    return remap(0, 100, 0, this.maxSpeed, value)
  }
}
