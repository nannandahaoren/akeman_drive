export class UI {
  constructor(options={}) {
    this.targetSpeed = document.querySelector('.target-speed')
    this.realSpeed = document.querySelector('.real-speed')
    this.targetAngle = document.querySelector('.target-angle')
    this.websocket = document.querySelector('.websocket-button')

    this.netState = document.querySelector('.net-state')
    this.netText = document.querySelector('.net-text')

    document.querySelector('.toggle').addEventListener('touchstart', () => {
      this.websocket.checked = !this.websocket.checked;
      this.netText.innerHTML = this.websocket.checked ? '连接中' : '等待';
      if(this.websocket.checked) {
        this.netState.classList.add('blink')
      } else {
        this.netState.classList.remove('blink')
      }

      // 网络点击事件
      options.netClick && options.netClick(this.websocket.checked)
    })
  }

  setNetState(state, text) {
    this.websocket.checked = state;
    this.netText.innerHTML = text;
    this.netState.classList.remove('blink')

    if (state) {
      this.netState.classList.remove('net-state-off');
      this.netState.classList.add('net-state-on');
    } else {
      this.netState.classList.add('net-state-off');
      this.netState.classList.remove('net-state-on');
    }
  }

  setTargetSpeed(speed) {
    this.targetSpeed.innerHTML = speed
  }

  setRealSpeed(speed) {
    this.realSpeed.innerHTML = speed
  }

  setTargetAngle(speed) {
    this.targetAngle.innerHTML = speed
  }
}
