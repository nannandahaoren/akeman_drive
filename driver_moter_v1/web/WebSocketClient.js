export class WebSocketClient {
  constructor(options = {}) {
    this.messageCallback = options.messageCallback;
    this.openCallback = options.openCallback;
    this.closeCallback = options.closeCallback;
    this.errorCallback = options.errorCallback;

    this.handleWsOpen = this.handleWsOpen.bind(this);
    this.handleWsClose = this.handleWsClose.bind(this);
    this.handleWsError = this.handleWsError.bind(this);
    this.handleWsMessage = this.handleWsMessage.bind(this);
  }

  open() {
    this.ws = new WebSocket('ws://192.168.109.191:81');
    this.ws.addEventListener("open", this.handleWsOpen, false);
    this.ws.addEventListener("close", this.handleWsClose, false);
    this.ws.addEventListener("error", this.handleWsError, false);
    this.ws.addEventListener("message", this.handleWsMessage, false);
  }

  close() {
    this.ws.close();
  }

  checkState() {
    let isOk = true;
    if (!this.ws) {
      isOk = false;
      return;
    }

    switch (this.ws.readyState) {
      case WebSocket.CONNECTING:
        isOk = false;
        break;
      case WebSocket.OPEN:
        isOk = true;
        break;
      case WebSocket.CLOSING:
        isOk = false;
        break;
      case WebSocket.CLOSED:
        isOk = false;
        break;
      default:
        break;
    }
    return isOk;
  }
  send(msg) {
    if (this.timer) {
      clearTimeout(this.timer);
    }


    this.timer = setTimeout(() => {
      if (this.checkState()) {
        this.ws.send(msg)
      }
      console.error(msg);

    }, 10);
  }

  // 这里接收后端send过来的数据
  handleWsMessage(e) {
    if (this.messageCallback) {
      this.messageCallback(e.data);
    }
  }

  handleWsOpen(e) {
    if (this.openCallback) {
      this.openCallback(e.data);
    }
    console.log("websocket open", e);
  }

  handleWsClose(e) {
    if (this.closeCallback) {
      this.closeCallback(e.data);
    }
    console.log("websocket close", e);
  }

  handleWsError(e) {
    console.log("websocket error", e);
    if (this.errorCallback) {
      this.errorCallback(e.data);
    }
  }
}
