//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/MTLTensor.hpp
//
// Copyright 2020-2025 Apple Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include "../Foundation/Foundation.hpp"
#include "MTLDefines.hpp"
#include "MTLHeaderBridge.hpp"
#include "MTLPrivate.hpp"
#include "MTLResource.hpp"
#include "MTLTypes.hpp"

namespace MTL
{
class Buffer;
class TensorAuxiliaryPlaneDescriptor;
class TensorAuxiliaryPlaneDescriptorMap;
class TensorBufferAttachments;
class TensorDescriptor;
class TensorExtents;

_MTL_CONST(NS::ErrorDomain, TensorDomain);

_MTL_ENUM(NS::Integer, TensorDataType) {
    TensorDataTypeNone = 0,
    TensorDataTypeFloat32 = 3,
    TensorDataTypeFloat16 = 16,
    TensorDataTypeBFloat16 = 121,
    TensorDataTypeInt8 = 45,
    TensorDataTypeUInt8 = 49,
    TensorDataTypeInt16 = 37,
    TensorDataTypeUInt16 = 41,
    TensorDataTypeInt32 = 29,
    TensorDataTypeUInt32 = 33,
    TensorDataTypeInt4 = 143,
    TensorDataTypeUInt4 = 144,
    TensorDataTypeMetalFloat8UE8M0 = 145,
    TensorDataTypeUInt2 = 149,
    TensorDataTypeInt2 = 150,
    TensorDataTypeMetalFloat8E5M2 = 141,
    TensorDataTypeMetalFloat8E4M3 = 142,
    TensorDataTypeMetalFloat4E2M1 = 148,
};

_MTL_ENUM(NS::Integer, TensorError) {
    TensorErrorNone = 0,
    TensorErrorInternalError = 1,
    TensorErrorInvalidDescriptor = 2,
};

_MTL_ENUM(NS::Integer, TensorPlaneType) {
    TensorPlaneTypeData = 0,
    TensorPlaneTypeScales = 1,
};

_MTL_OPTIONS(NS::UInteger, TensorUsage) {
    TensorUsageCompute = 1,
    TensorUsageRender = 1 << 1,
    TensorUsageMachineLearning = 1 << 2,
};

class TensorExtents : public NS::Copying<TensorExtents>
{
public:
    static TensorExtents* alloc();

    NS::Integer           extentAtDimensionIndex(NS::UInteger dimensionIndex);

    TensorExtents*        init();
    TensorExtents*        init(NS::UInteger rank, const NS::Integer* values);

    NS::UInteger          rank() const;
};
class TensorAuxiliaryPlaneDescriptor : public NS::Copying<TensorAuxiliaryPlaneDescriptor>
{
public:
    static TensorAuxiliaryPlaneDescriptor* alloc();

    TensorExtents*                         blockFactors() const;

    TensorDataType                         dataType() const;

    TensorAuxiliaryPlaneDescriptor*        init();

    void                                   setBlockFactors(const MTL::TensorExtents* blockFactors);

    void                                   setDataType(MTL::TensorDataType dataType);
};
class TensorAuxiliaryPlaneDescriptorMap : public NS::Copying<TensorAuxiliaryPlaneDescriptorMap>
{
public:
    static TensorAuxiliaryPlaneDescriptorMap* alloc();

    TensorAuxiliaryPlaneDescriptor*           descriptor(MTL::TensorPlaneType plane);

    TensorAuxiliaryPlaneDescriptorMap*        init();

    void                                      reset();

    void                                      setDescriptor(const MTL::TensorAuxiliaryPlaneDescriptor* descriptor, MTL::TensorPlaneType plane);
};
class TensorDescriptor : public NS::Copying<TensorDescriptor>
{
public:
    static TensorDescriptor*           alloc();

    TensorAuxiliaryPlaneDescriptorMap* auxiliaryPlanes() const;

    CPUCacheMode                       cpuCacheMode() const;

    TensorDataType                     dataType() const;

    TensorExtents*                     dimensions() const;

    HazardTrackingMode                 hazardTrackingMode() const;

    TensorDescriptor*                  init();

    ResourceOptions                    resourceOptions() const;

    void                               setAuxiliaryPlanes(const MTL::TensorAuxiliaryPlaneDescriptorMap* auxiliaryPlanes);

    void                               setCpuCacheMode(MTL::CPUCacheMode cpuCacheMode);

    void                               setDataType(MTL::TensorDataType dataType);

    void                               setDimensions(const MTL::TensorExtents* dimensions);

    void                               setHazardTrackingMode(MTL::HazardTrackingMode hazardTrackingMode);

    void                               setResourceOptions(MTL::ResourceOptions resourceOptions);

    void                               setStorageMode(MTL::StorageMode storageMode);

    void                               setStrides(const MTL::TensorExtents* strides);

    void                               setUsage(MTL::TensorUsage usage);

    StorageMode                        storageMode() const;

    TensorExtents*                     strides() const;

    TensorUsage                        usage() const;
};
class TensorBufferAttachments : public NS::Copying<TensorBufferAttachments>
{
public:
    static TensorBufferAttachments* alloc();

    Buffer*                         buffer(MTL::TensorPlaneType plane);

    TensorBufferAttachments*        init();

    NS::UInteger                    offset(MTL::TensorPlaneType plane);

    void                            reset();

    void                            setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, MTL::TensorPlaneType plane);
};
class TensorAuxiliaryPlane : public NS::Referencing<TensorAuxiliaryPlane>
{
public:
    TensorExtents*  blockFactors() const;

    Buffer*         buffer() const;
    NS::UInteger    bufferOffset() const;

    TensorDataType  dataType() const;

    TensorPlaneType planeType() const;
};
class Tensor : public NS::Referencing<Tensor, Resource>
{
public:
    NS::Array*     auxiliaryPlanes() const;

    Buffer*        buffer() const;
    NS::UInteger   bufferOffset() const;

    TensorDataType dataType() const;

    TensorExtents* dimensions() const;

    void           getBytes(void* bytes, const MTL::TensorExtents* strides, const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions);
    void           getBytes(void* bytes, const MTL::TensorExtents* strides, const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions, MTL::TensorPlaneType plane);

    ResourceID     gpuResourceID() const;

    void           replaceSliceOrigin(const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions, const void* bytes, const MTL::TensorExtents* strides);
    void           replaceSliceOrigin(const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions, MTL::TensorPlaneType plane, const void* bytes, const MTL::TensorExtents* strides);

    TensorExtents* strides() const;

    TensorUsage    usage() const;
};

}

_MTL_PRIVATE_DEF_CONST(NS::ErrorDomain, TensorDomain);

_MTL_INLINE MTL::TensorExtents* MTL::TensorExtents::alloc()
{
    return NS::Object::alloc<MTL::TensorExtents>(_MTL_PRIVATE_CLS(MTLTensorExtents));
}

_MTL_INLINE NS::Integer MTL::TensorExtents::extentAtDimensionIndex(NS::UInteger dimensionIndex)
{
    return Object::sendMessage<NS::Integer>(this, _MTL_PRIVATE_SEL(extentAtDimensionIndex_), dimensionIndex);
}

_MTL_INLINE MTL::TensorExtents* MTL::TensorExtents::init()
{
    return NS::Object::init<MTL::TensorExtents>();
}

_MTL_INLINE MTL::TensorExtents* MTL::TensorExtents::init(NS::UInteger rank, const NS::Integer* values)
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(initWithRank_values_), rank, values);
}

_MTL_INLINE NS::UInteger MTL::TensorExtents::rank() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(rank));
}

_MTL_INLINE MTL::TensorAuxiliaryPlaneDescriptor* MTL::TensorAuxiliaryPlaneDescriptor::alloc()
{
    return NS::Object::alloc<MTL::TensorAuxiliaryPlaneDescriptor>(_MTL_PRIVATE_CLS(MTLTensorAuxiliaryPlaneDescriptor));
}

_MTL_INLINE MTL::TensorExtents* MTL::TensorAuxiliaryPlaneDescriptor::blockFactors() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(blockFactors));
}

_MTL_INLINE MTL::TensorDataType MTL::TensorAuxiliaryPlaneDescriptor::dataType() const
{
    return Object::sendMessage<MTL::TensorDataType>(this, _MTL_PRIVATE_SEL(dataType));
}

_MTL_INLINE MTL::TensorAuxiliaryPlaneDescriptor* MTL::TensorAuxiliaryPlaneDescriptor::init()
{
    return NS::Object::init<MTL::TensorAuxiliaryPlaneDescriptor>();
}

_MTL_INLINE void MTL::TensorAuxiliaryPlaneDescriptor::setBlockFactors(const MTL::TensorExtents* blockFactors)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBlockFactors_), blockFactors);
}

_MTL_INLINE void MTL::TensorAuxiliaryPlaneDescriptor::setDataType(MTL::TensorDataType dataType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDataType_), dataType);
}

_MTL_INLINE MTL::TensorAuxiliaryPlaneDescriptorMap* MTL::TensorAuxiliaryPlaneDescriptorMap::alloc()
{
    return NS::Object::alloc<MTL::TensorAuxiliaryPlaneDescriptorMap>(_MTL_PRIVATE_CLS(MTLTensorAuxiliaryPlaneDescriptorMap));
}

_MTL_INLINE MTL::TensorAuxiliaryPlaneDescriptor* MTL::TensorAuxiliaryPlaneDescriptorMap::descriptor(MTL::TensorPlaneType plane)
{
    return Object::sendMessage<MTL::TensorAuxiliaryPlaneDescriptor*>(this, _MTL_PRIVATE_SEL(descriptorForPlane_), plane);
}

_MTL_INLINE MTL::TensorAuxiliaryPlaneDescriptorMap* MTL::TensorAuxiliaryPlaneDescriptorMap::init()
{
    return NS::Object::init<MTL::TensorAuxiliaryPlaneDescriptorMap>();
}

_MTL_INLINE void MTL::TensorAuxiliaryPlaneDescriptorMap::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

_MTL_INLINE void MTL::TensorAuxiliaryPlaneDescriptorMap::setDescriptor(const MTL::TensorAuxiliaryPlaneDescriptor* descriptor, MTL::TensorPlaneType plane)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDescriptor_forPlane_), descriptor, plane);
}

_MTL_INLINE MTL::TensorDescriptor* MTL::TensorDescriptor::alloc()
{
    return NS::Object::alloc<MTL::TensorDescriptor>(_MTL_PRIVATE_CLS(MTLTensorDescriptor));
}

_MTL_INLINE MTL::TensorAuxiliaryPlaneDescriptorMap* MTL::TensorDescriptor::auxiliaryPlanes() const
{
    return Object::sendMessage<MTL::TensorAuxiliaryPlaneDescriptorMap*>(this, _MTL_PRIVATE_SEL(auxiliaryPlanes));
}

_MTL_INLINE MTL::CPUCacheMode MTL::TensorDescriptor::cpuCacheMode() const
{
    return Object::sendMessage<MTL::CPUCacheMode>(this, _MTL_PRIVATE_SEL(cpuCacheMode));
}

_MTL_INLINE MTL::TensorDataType MTL::TensorDescriptor::dataType() const
{
    return Object::sendMessage<MTL::TensorDataType>(this, _MTL_PRIVATE_SEL(dataType));
}

_MTL_INLINE MTL::TensorExtents* MTL::TensorDescriptor::dimensions() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(dimensions));
}

_MTL_INLINE MTL::HazardTrackingMode MTL::TensorDescriptor::hazardTrackingMode() const
{
    return Object::sendMessage<MTL::HazardTrackingMode>(this, _MTL_PRIVATE_SEL(hazardTrackingMode));
}

_MTL_INLINE MTL::TensorDescriptor* MTL::TensorDescriptor::init()
{
    return NS::Object::init<MTL::TensorDescriptor>();
}

_MTL_INLINE MTL::ResourceOptions MTL::TensorDescriptor::resourceOptions() const
{
    return Object::sendMessage<MTL::ResourceOptions>(this, _MTL_PRIVATE_SEL(resourceOptions));
}

_MTL_INLINE void MTL::TensorDescriptor::setAuxiliaryPlanes(const MTL::TensorAuxiliaryPlaneDescriptorMap* auxiliaryPlanes)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setAuxiliaryPlanes_), auxiliaryPlanes);
}

_MTL_INLINE void MTL::TensorDescriptor::setCpuCacheMode(MTL::CPUCacheMode cpuCacheMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setCpuCacheMode_), cpuCacheMode);
}

_MTL_INLINE void MTL::TensorDescriptor::setDataType(MTL::TensorDataType dataType)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDataType_), dataType);
}

_MTL_INLINE void MTL::TensorDescriptor::setDimensions(const MTL::TensorExtents* dimensions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setDimensions_), dimensions);
}

_MTL_INLINE void MTL::TensorDescriptor::setHazardTrackingMode(MTL::HazardTrackingMode hazardTrackingMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setHazardTrackingMode_), hazardTrackingMode);
}

_MTL_INLINE void MTL::TensorDescriptor::setResourceOptions(MTL::ResourceOptions resourceOptions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setResourceOptions_), resourceOptions);
}

_MTL_INLINE void MTL::TensorDescriptor::setStorageMode(MTL::StorageMode storageMode)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStorageMode_), storageMode);
}

_MTL_INLINE void MTL::TensorDescriptor::setStrides(const MTL::TensorExtents* strides)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setStrides_), strides);
}

_MTL_INLINE void MTL::TensorDescriptor::setUsage(MTL::TensorUsage usage)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setUsage_), usage);
}

_MTL_INLINE MTL::StorageMode MTL::TensorDescriptor::storageMode() const
{
    return Object::sendMessage<MTL::StorageMode>(this, _MTL_PRIVATE_SEL(storageMode));
}

_MTL_INLINE MTL::TensorExtents* MTL::TensorDescriptor::strides() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(strides));
}

_MTL_INLINE MTL::TensorUsage MTL::TensorDescriptor::usage() const
{
    return Object::sendMessage<MTL::TensorUsage>(this, _MTL_PRIVATE_SEL(usage));
}

_MTL_INLINE MTL::TensorBufferAttachments* MTL::TensorBufferAttachments::alloc()
{
    return NS::Object::alloc<MTL::TensorBufferAttachments>(_MTL_PRIVATE_CLS(MTLTensorBufferAttachments));
}

_MTL_INLINE MTL::Buffer* MTL::TensorBufferAttachments::buffer(MTL::TensorPlaneType plane)
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(bufferForPlane_), plane);
}

_MTL_INLINE MTL::TensorBufferAttachments* MTL::TensorBufferAttachments::init()
{
    return NS::Object::init<MTL::TensorBufferAttachments>();
}

_MTL_INLINE NS::UInteger MTL::TensorBufferAttachments::offset(MTL::TensorPlaneType plane)
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(offsetForPlane_), plane);
}

_MTL_INLINE void MTL::TensorBufferAttachments::reset()
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(reset));
}

_MTL_INLINE void MTL::TensorBufferAttachments::setBuffer(const MTL::Buffer* buffer, NS::UInteger offset, MTL::TensorPlaneType plane)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(setBuffer_offset_forPlane_), buffer, offset, plane);
}

_MTL_INLINE MTL::TensorExtents* MTL::TensorAuxiliaryPlane::blockFactors() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(blockFactors));
}

_MTL_INLINE MTL::Buffer* MTL::TensorAuxiliaryPlane::buffer() const
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(buffer));
}

_MTL_INLINE NS::UInteger MTL::TensorAuxiliaryPlane::bufferOffset() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(bufferOffset));
}

_MTL_INLINE MTL::TensorDataType MTL::TensorAuxiliaryPlane::dataType() const
{
    return Object::sendMessage<MTL::TensorDataType>(this, _MTL_PRIVATE_SEL(dataType));
}

_MTL_INLINE MTL::TensorPlaneType MTL::TensorAuxiliaryPlane::planeType() const
{
    return Object::sendMessage<MTL::TensorPlaneType>(this, _MTL_PRIVATE_SEL(planeType));
}

_MTL_INLINE NS::Array* MTL::Tensor::auxiliaryPlanes() const
{
    return Object::sendMessage<NS::Array*>(this, _MTL_PRIVATE_SEL(auxiliaryPlanes));
}

_MTL_INLINE MTL::Buffer* MTL::Tensor::buffer() const
{
    return Object::sendMessage<MTL::Buffer*>(this, _MTL_PRIVATE_SEL(buffer));
}

_MTL_INLINE NS::UInteger MTL::Tensor::bufferOffset() const
{
    return Object::sendMessage<NS::UInteger>(this, _MTL_PRIVATE_SEL(bufferOffset));
}

_MTL_INLINE MTL::TensorDataType MTL::Tensor::dataType() const
{
    return Object::sendMessage<MTL::TensorDataType>(this, _MTL_PRIVATE_SEL(dataType));
}

_MTL_INLINE MTL::TensorExtents* MTL::Tensor::dimensions() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(dimensions));
}

_MTL_INLINE void MTL::Tensor::getBytes(void* bytes, const MTL::TensorExtents* strides, const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(getBytes_strides_fromSliceOrigin_sliceDimensions_), bytes, strides, sliceOrigin, sliceDimensions);
}

_MTL_INLINE void MTL::Tensor::getBytes(void* bytes, const MTL::TensorExtents* strides, const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions, MTL::TensorPlaneType plane)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(getBytes_strides_fromSliceOrigin_sliceDimensions_plane_), bytes, strides, sliceOrigin, sliceDimensions, plane);
}

_MTL_INLINE MTL::ResourceID MTL::Tensor::gpuResourceID() const
{
    return Object::sendMessage<MTL::ResourceID>(this, _MTL_PRIVATE_SEL(gpuResourceID));
}

_MTL_INLINE void MTL::Tensor::replaceSliceOrigin(const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions, const void* bytes, const MTL::TensorExtents* strides)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(replaceSliceOrigin_sliceDimensions_withBytes_strides_), sliceOrigin, sliceDimensions, bytes, strides);
}

_MTL_INLINE void MTL::Tensor::replaceSliceOrigin(const MTL::TensorExtents* sliceOrigin, const MTL::TensorExtents* sliceDimensions, MTL::TensorPlaneType plane, const void* bytes, const MTL::TensorExtents* strides)
{
    Object::sendMessage<void>(this, _MTL_PRIVATE_SEL(replaceSliceOrigin_sliceDimensions_plane_withBytes_strides_), sliceOrigin, sliceDimensions, plane, bytes, strides);
}

_MTL_INLINE MTL::TensorExtents* MTL::Tensor::strides() const
{
    return Object::sendMessage<MTL::TensorExtents*>(this, _MTL_PRIVATE_SEL(strides));
}

_MTL_INLINE MTL::TensorUsage MTL::Tensor::usage() const
{
    return Object::sendMessage<MTL::TensorUsage>(this, _MTL_PRIVATE_SEL(usage));
}
