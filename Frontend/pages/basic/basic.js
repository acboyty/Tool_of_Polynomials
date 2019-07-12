//index.js
//获取应用实例
const app = getApp()

Page({
  data: {
    cxk: '/images/cxk_waiting.jpg',
    poly1: '',
    poly2: '',
    oper: '0',
    array: ['addition', 'subtraction', 'multiplication', 'division'],
    ans: ''
  },
  polyInput1: function (e) {
    this.setData({
      poly1: e.detail.value
    })
  },
  polyInput2: function (e) {
    this.setData({
      poly2: e.detail.value
    })
  },
  bindPickerChange: function (e) {
    this.setData({
      index: e.detail.value,
      oper: e.detail.value
    })
  },
  calculate: function (e) {
    this.setData({
      cxk: '/images/cxk_waiting.jpg',
    })
    console.log(this.data.poly1);
    console.log(this.data.poly2);
    console.log(this.data.oper);
    wx.request({
      url: 'https://polynomials.ngrok.xiaomiqiu.cn/Tool_of_Polynomials_war_exploded/Calculate?' + 'poly1=' + this.data.poly1 + '&poly2=' + this.data.poly2 + '&oper=' + this.data.oper,
      data: '',
      header: {
        'content-type': 'application/json'
      },
      method: 'GET',
      success: res => {
        if (res.data == '') {
          this.setData({
            cxk: '/images/cxk_fail.jpg',
            ans: 'failed'
          })
        }
        else {
          this.setData({
            cxk: '/images/cxk_success.jpg',
            ans: res.data
          })
        }
      }
    })
  }
})
