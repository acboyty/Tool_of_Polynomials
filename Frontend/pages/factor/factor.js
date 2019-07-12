//index.js
//获取应用实例
//const app = getApp()

Page({
  data: {
    cxk: '/images/cxk_waiting.jpg',
    poly: '',
    factors: ''
  },
  polyInput: function(e) {
    this.setData({
      poly: e.detail.value
    })
  },
  get_factors: function(e) {
    this.setData({
      cxk: '/images/cxk_waiting.jpg',
    })
    wx.request({
      url: 'https://polynomials.ngrok.xiaomiqiu.cn/Tool_of_Polynomials_war_exploded/Factor?poly=' + this.data.poly,
      data: '',
      header: {
        'content-type': 'application/json'
      },
      method: 'GET',
      success: res => {
        if (res.data == '') {
          this.setData({
            cxk: '/images/cxk_fail.jpg',
            factors: 'failed'
          })
        }
        else {
          this.setData({
            cxk: '/images/cxk_success.jpg',
            factors: res.data
          })
        }
      }
    })
  }
})
