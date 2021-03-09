/*
 * (C) Copyright 2016 Kurento (http://kurento.org/)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <gst/gst.h>
#include "MediaPipeline.hpp"
#include <CompositeImplFactory.hpp>
#include "CompositeImpl.hpp"
#include <jsonrpc/JsonSerializer.hpp>
#include <KurentoException.hpp>
#include <gst/gst.h>

#define GST_CAT_DEFAULT kurento_composite_impl
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);
#define GST_DEFAULT_NAME "KurentoCompositeImpl"

#define FACTORY_NAME "compositemixer"
#define SET_PROPERTIES "set-properties"

namespace kurento
{

CompositeImpl::CompositeImpl (const boost::property_tree::ptree &conf,
                              std::shared_ptr<MediaPipeline> mediaPipeline,
                              int mode, int outputWidth, int outputHeight,
                              int aspectX, int aspectY, int cellWidth,
                              int cellHeight, int maxNColumns, int xyGap) : HubImpl (conf,
                                    std::dynamic_pointer_cast<MediaObjectImpl> (mediaPipeline), FACTORY_NAME)
{
  GstStructure *data;

  GST_DEBUG ("set composite properties");
  data = gst_structure_new ("data",
                            "mode", G_TYPE_INT, mode,
                            "output_width", G_TYPE_INT, outputWidth,
                            "output_height", G_TYPE_INT, outputHeight,
                            "aspect_x", G_TYPE_INT, aspectX,
                            "aspect_y", G_TYPE_INT, aspectY,
                            "cell_width", G_TYPE_INT, cellWidth,
                            "cell_height", G_TYPE_INT, cellHeight,
                            "max_n_columns", G_TYPE_INT, maxNColumns,
                            "xy_gap", G_TYPE_INT, xyGap,
                            NULL);

  g_object_set (G_OBJECT (element), SET_PROPERTIES, data, NULL);
  gst_structure_free (data);
}

MediaObjectImpl *
CompositeImplFactory::createObject (const boost::property_tree::ptree &conf,
                                    std::shared_ptr<MediaPipeline> mediaPipeline,
                                    int mode, int outputWidth, int outputHeight,
                                    int aspectX, int aspectY, int cellWidth,
                                    int cellHeight, int maxNColumns, int xyGap) const
{
  return new CompositeImpl (conf, mediaPipeline, mode, outputWidth, outputHeight,
                            aspectX, aspectY, cellWidth, cellHeight, maxNColumns, xyGap);
}

CompositeImpl::StaticConstructor CompositeImpl::staticConstructor;

CompositeImpl::StaticConstructor::StaticConstructor()
{
  GST_DEBUG_CATEGORY_INIT (GST_CAT_DEFAULT, GST_DEFAULT_NAME, 0,
                           GST_DEFAULT_NAME);
}

} /* kurento */
