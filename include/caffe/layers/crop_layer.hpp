// #ifndef CAFFE_VISION_LAYERS_HPP_
// #define CAFFE_VISION_LAYERS_HPP_

#include <string>
#include <utility>
#include <vector>

#include "caffe/blob.hpp"
#include "caffe/common.hpp"
// #include "caffe/common_layers.hpp"
// #include "caffe/data_layers.hpp"
#include "caffe/layer.hpp"
// #include "caffe/loss_layers.hpp"
// #include "caffe/neuron_layers.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

template <typename Dtype>
class CropLayer : public Layer<Dtype> {
 public:
  explicit CropLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "Crop"; }
  virtual inline int ExactNumBottomBlobs() const { return 2; }
  virtual inline int ExactNumTopBlobs() const { return 1; }
  virtual inline DiagonalAffineMap<Dtype> coord_map() {
    vector<pair<Dtype, Dtype> > coefs;
    coefs.push_back(make_pair(1, - crop_h_));
    coefs.push_back(make_pair(1, - crop_w_));
    return DiagonalAffineMap<Dtype>(coefs);
  }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

  int crop_h_, crop_w_;
};

} // namespace caffe