// -*- mode: c++; -*-
/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2024, rcp1
 *  Copyright (c) 2014, JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the JSK Lab nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
#ifndef JSK_RVIZ_PLUGIN_PLOTTER_2D_HPP_
#define JSK_RVIZ_PLUGIN_PLOTTER_2D_HPP_

#include <mutex>

#include "ros_babel_fish_topic_display.hpp"
#include "std_msgs/msg/float32.hpp"
#ifndef Q_MOC_RUN
  #include <rviz_common/display.hpp>
  #include "overlay_utils.hpp"
  #include <OgreColourValue.h>
  #include <OgreTexture.h>
  #include <OgreMaterial.h>
  #include <rviz_common/properties/bool_property.hpp>
  #include <rviz_common/properties/color_property.hpp>
  #include <rviz_common/properties/float_property.hpp>
  #include <rviz_common/properties/int_property.hpp>
  #include <rviz_common/properties/string_property.hpp>
  #include <rviz_common/properties/ros_topic_property.hpp>
#endif

namespace rviz_2d_overlay_plugins
{

  class Plotter2DDisplay
    : public RosBabelFishTopicDisplay
  {
    Q_OBJECT
  public:
    Plotter2DDisplay();
    virtual ~Plotter2DDisplay();
    // methods for OverlayPickerTool
    virtual bool isInRegion(int x, int y);
    virtual void movePosition(int x, int y);
    virtual void setPosition(int x, int y);
    virtual int getX() const { return left_; };
    virtual int getY() const { return top_; };
  protected:
    ////////////////////////////////////////////////////////
    // methods
    ////////////////////////////////////////////////////////
    virtual void update(float wall_dt, float ros_dt);
    virtual void onEnable();
    virtual void onDisable();
    virtual void initializeBuffer();
    virtual void onInitialize();
    virtual double recurseToField(const ros_babel_fish::Message & msg, size_t topic_field_idx);
    virtual void processMessage(ros_babel_fish::CompoundMessage::ConstSharedPtr msg) override;
    virtual void drawPlot();
    ////////////////////////////////////////////////////////
    // properties
    ////////////////////////////////////////////////////////
    std::unique_ptr<rviz_common::properties::StringProperty> topic_message_type_property_;
    std::unique_ptr<rviz_common::properties::StringProperty> topic_field_property_;
    std::unique_ptr<rviz_common::properties::BoolProperty> show_value_property_;
    std::unique_ptr<rviz_common::properties::ColorProperty> fg_color_property_;
    std::unique_ptr<rviz_common::properties::ColorProperty> bg_color_property_;
    std::unique_ptr<rviz_common::properties::FloatProperty> fg_alpha_property_;
    std::unique_ptr<rviz_common::properties::FloatProperty> bg_alpha_property_;
    std::unique_ptr<rviz_common::properties::FloatProperty> update_interval_property_;
    std::unique_ptr<rviz_common::properties::BoolProperty> show_border_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> buffer_length_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> width_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> height_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> left_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> top_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> line_width_property_;
    std::unique_ptr<rviz_common::properties::BoolProperty> auto_color_change_property_;
    std::unique_ptr<rviz_common::properties::ColorProperty> max_color_property_;
    std::unique_ptr<rviz_common::properties::BoolProperty> show_caption_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> text_size_property_;
    std::unique_ptr<rviz_common::properties::BoolProperty> auto_scale_property_;
    std::unique_ptr<rviz_common::properties::FloatProperty> max_value_property_;
    std::unique_ptr<rviz_common::properties::FloatProperty> min_value_property_;
    std::unique_ptr<rviz_common::properties::BoolProperty> auto_text_size_in_plot_property_;
    std::unique_ptr<rviz_common::properties::IntProperty> text_size_in_plot_property_;

    QString topic_message_type_;
    std::string topic_field_;
    std::vector<std::string> topic_fields_;
    rviz_2d_overlay_plugins::OverlayObject::SharedPtr overlay_;
    QColor fg_color_;
    QColor max_color_;
    QColor bg_color_;

    double fg_alpha_;
    double bg_alpha_;
    bool auto_scale_;
    bool show_border_;
    bool auto_color_change_;
    bool show_value_;
    bool show_caption_;
    bool draw_required_;
    float last_time_;
    float update_interval_;
    bool auto_text_size_in_plot_;
    int text_size_in_plot_;

    int buffer_length_;
    std::vector<double> buffer_;
    uint16_t texture_width_;
    uint16_t texture_height_;
    int left_;
    int top_;
    int line_width_;
    int text_size_;
    int caption_offset_;
    double min_value_;
    double max_value_;

    ////////////////////////////////////////////////////////
    // ROS variables
    ////////////////////////////////////////////////////////
    std::mutex mutex_;

  protected Q_SLOTS:
    void updateTopicMessageType();
    void updateTopicField();
    void updateShowValue();
    void updateBufferSize();
    void updateBGColor();
    void updateFGColor();
    void updateFGAlpha();
    void updateBGAlpha();
    void updateWidth();
    void updateHeight();
    void updateTop();
    void updateLeft();
    void updateLineWidth();
    void updateShowBorder();
    void updateAutoColorChange();
    void updateMaxColor();
    void updateUpdateInterval();
    void updateShowCaption();
    void updateTextSize();
    void updateAutoScale();
    void updateMinValue();
    void updateMaxValue();
    void updateTextSizeInPlot();
    void updateAutoTextSizeInPlot();

  private:
  };
}  // namespace rviz_2d_overlay_plugins

#endif  // JSK_RVIZ_PLUGIN_PLOTTER_2D_HPP_
