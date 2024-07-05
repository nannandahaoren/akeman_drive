export class Chart {
  constructor() {
    // 基于准备好的dom，初始化echarts实例
    this.chart = echarts.init(document.getElementById('main'));

    // 初始化目标速度和实际速度数据
    this.targetSpeed = [];
    this.actualSpeed = [];

    // 配置图表选项
    var option = {
      title: {
        text: 'PID 调试'
      },
      legend: {
        data: ['目标速度', '实际速度']
      },
      xAxis: {
        type: 'category',
        data: []  // 横轴数据为空，后续动态更新
      },
      yAxis: {},
      series: [{
        name: '目标速度',
        type: 'line',
        data: this.targetSpeed  // 目标速度数据
      }, {
        name: '实际速度',
        type: 'line',
        data: this.actualSpeed  // 实际速度数据
      }]
    };

    // 使用配置项显示图表
    this.chart.setOption(option);

    // 模拟实时更新数据
    // setInterval(function () {
    //   // 通过异步请求获取最新的目标速度和实际速度数据
    //   // 这里使用随机数生成示例数据
    //   var newTargetSpeed = Math.random() * 100;
    //   var newActualSpeed = Math.random() * 100;


    // }, 1000);  // 每秒更新一次数据
  }

  pushData(target, read) {
    // console.error(target, read);

    // 将最新数据添加到数据数组中
    this.targetSpeed.push(target);
    this.actualSpeed.push(read);

    // 只保留最近的一定数量的数据，以控制折线图的显示范围
    var maxDataCount = 50;  // 最大数据点数量
    if (this.targetSpeed.length > maxDataCount) {
      this.targetSpeed.shift();
      this.actualSpeed.shift();
    }

    // 更新横轴数据
    var xAxisData = [];
    for (var i = 0; i < this.targetSpeed.length; i++) {
      xAxisData.push(i);
    }
    this.chart.setOption({
      xAxis: {
        data: xAxisData
      },
      series: [{
        data: this.targetSpeed
      }, {
        data: this.actualSpeed
      }]
    });
  }
}
