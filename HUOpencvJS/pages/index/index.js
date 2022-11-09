// pages/huTest/huTest.js
const app = getApp();
// 画布
const canvas1 = 'canvas1'
// 示例图片
const sampleImage1 = '/images/shenhe.jpeg'
// 画布最大宽度
const maxCanvasWidth = 375
// wasm路径
global.wasm_url = '/OpenCV/opencv_js.wasm.br'
// opencv.js会从global.wasm_url获取wasm路径
let cv = require('../../OpenCV/opencv');

Page({

  /**
   * 页面的初始数据
   */
  data: {
    canvas1Width: 375,
    canvas1Height: 150,
    // 示例图片
    sampleImage1Url: sampleImage1,
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    // 可见的画布
    this.initCanvas(canvas1)
    cv.then( (result) => {
      cv = result;
      console.info('初始化 OpenCV', cv);
    })
  },
  // 获取画布
  initCanvas(canvasId) {
    var _that = this;
    wx.createSelectorQuery()
      .select('#' + canvasId)
      .fields({
        node: true,
        size: true
      })
      .exec((res) => {
        const canvas2d = res[0].node;
        // 设置画布的宽度和高度
        canvas2d.width = res[0].width;
        canvas2d.height = res[0].height;
        _that.canvasDom = canvas2d
      });
  },
  	// 获取图像数据和调整图像大小
	getImageData(image,offscreenCanvas) {
		var _that = this
		// const ctx = wx.createCanvasContext(canvasId);
		var canvasWidth = image.width;
		if (canvasWidth > maxCanvasWidth) {
			canvasWidth = maxCanvasWidth;
		}
		// canvas Height
		var canvasHeight = Math.floor(canvasWidth * (image.height / image.width));
		// 离屏画布的宽度和高度不能小于图像的
		offscreenCanvas.width = canvasWidth;
		offscreenCanvas.height = canvasHeight;
		// draw image on canvas
		var ctx = offscreenCanvas.getContext('2d')
		ctx.drawImage(image, 0, 0, canvasWidth, canvasHeight);
		// get image data from canvas
    var imgData = ctx.getImageData(0, 0, canvasWidth, canvasHeight);

		return imgData
  },
  // 创建图像对象
	async createImageElement(imgUrl) {
		var _that = this
		// 创建2d类型的离屏画布(需要微信基础库2.16.1以上)
		var offscreenCanvas = wx.createOffscreenCanvas({type: '2d'});
		const image = offscreenCanvas.createImage();
		await new Promise(function (resolve, reject) {
			image.onload = resolve
			image.onerror = reject
			image.src = imgUrl
		})
		const imageData = _that.getImageData(image,offscreenCanvas)
		return imageData
	},
	imgProcess1(imageData, canvasDom) {
    // 读取图像
		let src = cv.imread(imageData);
		let dst = new cv.Mat();
		// 灰度化
		cv.cvtColor(src, dst, cv.COLOR_RGBA2GRAY, 0);
    // 显示图像
		cv.imshow(canvasDom, dst);
		// 回收对象
		src.delete();
		dst.delete()
	},
	imgProcess2(imageData, canvasDom) {
		let src = cv.imread(imageData);
		let dst = new cv.Mat();

		// 灰度化
		cv.cvtColor(src, src, cv.COLOR_RGBA2GRAY, 0);
		// 边缘检测
		cv.Canny(src, dst, 50, 100, 3, false);

		cv.imshow(canvasDom, dst);
		src.delete();
		dst.delete()
	},

  async btnRun1() {
		var _that = this;
		// 将图像转换为ImageData
    const image1Data = await _that.createImageElement(sampleImage1)
    console.info("创建 imagedata ", image1Data);
		// 设置画布的显示大小
		_that.setData({
			canvas1Width: image1Data.width,
			canvas1Height: image1Data.height,
		})
		_that.imgProcess1(image1Data, _that.canvasDom)
	},
	async btnRun2() {
		// 同上
		var _that = this;
		const image1Data = await _that.createImageElement(sampleImage1)
		_that.setData({
			canvas1Width: image1Data.width,
			canvas1Height: image1Data.height,
		})
		_that.imgProcess2(image1Data, _that.canvasDom)
	},
})