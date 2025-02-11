/* eslint-disable no-undef */

/***
 * modal.alert(Object)
 */
function FilePicker () {
  var defaultOpts = {
    id: 'filepicker',
    module: 'filepicker',
    page: true,
    methods: ['open'],
    source: '../qml/SFilesPicker.qml'
  }
  SyberPlugin.call(this, defaultOpts)

  var that = this

    this.on('open', function (object, handlerId, param) {
        var component = object || that.object

        component.titleText = that.param.title || ""
        component.leftItemEnabled = that.param.showBack || false
        component.categoryType = that.param.category || "all"
        component.count = that.param.count || 1


        component.ok.connect(function(filesPath) { //处理选择文件信号
            console.log('filepicker.ok filesPath: ', filesPath)
            pageStack.pop()
            that.success(that.handlerId, { files: filesPath })
        })

        component.cancel.connect(function() { //处理取消信号
            pageStack.pop()
            that.success(that.handlerId)
        })

    })
}

FilePicker.prototype = SyberPlugin.prototype
