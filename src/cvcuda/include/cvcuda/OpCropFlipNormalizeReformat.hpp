/*
 * SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file OpCropFlipNormalizeReformat.hpp
 *
 * @brief Defines the public C++ Class for the CropFlipNormalizeReformat operation.
 * @defgroup NVCV_CPP_ALGORITHM_CROP_FLIP_NORMALIZE_REFORMAT CropFlipNormalizeReformat
 * @{
 */

#ifndef CVCUDA_CROP_FLIP_NORMALIZE_REFORMAT_HPP
#define CVCUDA_CROP_FLIP_NORMALIZE_REFORMAT_HPP

#include "IOperator.hpp"
#include "OpCropFlipNormalizeReformat.h"

#include <cuda_runtime.h>
#include <nvcv/IImageBatch.hpp>
#include <nvcv/ITensor.hpp>
#include <nvcv/ImageFormat.hpp>
#include <nvcv/alloc/Requirements.hpp>

namespace cvcuda {

class CropFlipNormalizeReformat final : public IOperator
{
public:
    explicit CropFlipNormalizeReformat();

    ~CropFlipNormalizeReformat();

    void operator()(cudaStream_t stream, nvcv::IImageBatch &in, nvcv::ITensor &out, nvcv::ITensor &cropRect,
                    NVCVBorderType borderMode, float borderValue, nvcv::ITensor &flipCode, nvcv::ITensor &base,
                    nvcv::ITensor &scale, float global_scale, float shift, float epsilon, uint32_t flags = 0);

    virtual NVCVOperatorHandle handle() const noexcept override;

private:
    NVCVOperatorHandle m_handle;
};

inline CropFlipNormalizeReformat::CropFlipNormalizeReformat()
{
    nvcv::detail::CheckThrow(cvcudaCropFlipNormalizeReformatCreate(&m_handle));
    assert(m_handle);
}

inline CropFlipNormalizeReformat::~CropFlipNormalizeReformat()
{
    nvcvOperatorDestroy(m_handle);
    m_handle = nullptr;
}

inline void CropFlipNormalizeReformat::operator()(cudaStream_t stream, nvcv::IImageBatch &in, nvcv::ITensor &out,
                                                  nvcv::ITensor &cropRect, NVCVBorderType borderMode, float borderValue,
                                                  nvcv::ITensor &flipCode, nvcv::ITensor &base, nvcv::ITensor &scale,
                                                  float global_scale, float shift, float epsilon, uint32_t flags)
{
    nvcv::detail::CheckThrow(cvcudaCropFlipNormalizeReformatSubmit(
        m_handle, stream, in.handle(), out.handle(), cropRect.handle(), borderMode, borderValue, flipCode.handle(),
        base.handle(), scale.handle(), global_scale, shift, epsilon, flags));
}

inline NVCVOperatorHandle CropFlipNormalizeReformat::handle() const noexcept
{
    return m_handle;
}

} // namespace cvcuda

#endif // CVCUDA_CROP_FLIP_NORMALIZE_REFORMAT_HPP
