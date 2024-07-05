import { WebSocketClient } from './WebSocketClient.js'
import { Chart } from './chart.js';
const chart = new Chart();

var targetSpeed = 0;
var angle = 0;
let isForword = true;

const socket = new WebSocketClient({
  messageCallback: e => {
    const v = e.split(',');
    // updateActualSpeed(v[0])
    chart.pushData(v[1], v[0])
  },
  openCallback: () => {
    document.getElementById("connectionStatus").textContent = "连接成功";
  },
  closeCallback: () => {
    document.getElementById("connectionStatus").textContent = "连接断开";
  },
  errorCallback: () => {
    document.getElementById("connectionStatus").textContent = "连接错误";
  }
});

function updateActualSpeed(actualSpeed) {
  // 假设在此处编写代码更新实际速度的逻辑
  // var actualSpeed = 0; // 替换为实际速度的计算值
  // document.getElementById("actualSpeedValue").textContent = actualSpeed;

}

function sendMessage() {
  // 0: 目标速度
  // 1: 舵机角度

  // ui: -90~90
  // servo: 0~180
  const msg = `${targetSpeed * (isForword ? 1 : -1)},${+angle}`;
  console.error(msg);

  socket.send(msg)
}

window.updateTargetSpeed = () => {
  var slider = document.getElementById("targetSpeedSlider");
  targetSpeed = slider.value;
  document.getElementById("targetSpeedValue").textContent = targetSpeed;

  sendMessage();
};

window.toggleSwitch = () => {
  var switchButton = document.getElementById("switch");
  switchButton.classList.toggle("on");
  switchButton.classList.toggle("off");

  isForword = !isForword;
  document.querySelector(".dir").innerHTML = isForword ? '前进' : "后退"
}

window.updateAngle = () => {
  var slider = document.getElementById("angleSlider");
  angle = slider.value;
  document.getElementById("angleValue").textContent = angle;
  sendMessage();
};

document.getElementById("connectionStatus").textContent = "等待连接";
window.openWebSocket = () => {
  socket.open();
  document.getElementById("connectionStatus").textContent = "连接中...";
}

window.closeWebSocket = () => {
  socket.close();
}
