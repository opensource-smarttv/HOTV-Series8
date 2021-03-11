# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'bindings_core_v8_output_dir': '<(SHARED_INTERMEDIATE_DIR)/blink/bindings/core/v8',
    'bindings_core_v8_generated_union_type_files': [
      '<(bindings_core_v8_output_dir)/AddEventListenerOptionsOrBoolean.cpp',
      '<(bindings_core_v8_output_dir)/AddEventListenerOptionsOrBoolean.h',
      '<(bindings_core_v8_output_dir)/ArrayBufferOrArrayBufferView.cpp',
      '<(bindings_core_v8_output_dir)/ArrayBufferOrArrayBufferView.h',
      '<(bindings_core_v8_output_dir)/ArrayBufferOrArrayBufferViewOrBlobOrDocumentOrStringOrFormData.cpp',
      '<(bindings_core_v8_output_dir)/ArrayBufferOrArrayBufferViewOrBlobOrDocumentOrStringOrFormData.h',
      '<(bindings_core_v8_output_dir)/ArrayBufferOrArrayBufferViewOrBlobOrUSVString.cpp',
      '<(bindings_core_v8_output_dir)/ArrayBufferOrArrayBufferViewOrBlobOrUSVString.h',
      '<(bindings_core_v8_output_dir)/CSSStyleValueOrCSSStyleValueSequence.cpp',
      '<(bindings_core_v8_output_dir)/CSSStyleValueOrCSSStyleValueSequence.h',
      '<(bindings_core_v8_output_dir)/CSSStyleValueOrCSSStyleValueSequenceOrString.cpp',
      '<(bindings_core_v8_output_dir)/CSSStyleValueOrCSSStyleValueSequenceOrString.h',
      '<(bindings_core_v8_output_dir)/DoubleOrAutoKeyword.cpp',
      '<(bindings_core_v8_output_dir)/DoubleOrAutoKeyword.h',
      '<(bindings_core_v8_output_dir)/DoubleOrDoubleArray.cpp',
      '<(bindings_core_v8_output_dir)/DoubleOrDoubleArray.h',
      '<(bindings_core_v8_output_dir)/DoubleOrInternalEnum.cpp',
      '<(bindings_core_v8_output_dir)/DoubleOrInternalEnum.h',
      '<(bindings_core_v8_output_dir)/DoubleOrString.cpp',
      '<(bindings_core_v8_output_dir)/DoubleOrString.h',
      '<(bindings_core_v8_output_dir)/DoubleOrStringOrStringArray.cpp',
      '<(bindings_core_v8_output_dir)/DoubleOrStringOrStringArray.h',
      '<(bindings_core_v8_output_dir)/DoubleOrStringOrStringSequence.cpp',
      '<(bindings_core_v8_output_dir)/DoubleOrStringOrStringSequence.h',
      '<(bindings_core_v8_output_dir)/EffectModelOrDictionarySequenceOrDictionary.cpp',
      '<(bindings_core_v8_output_dir)/EffectModelOrDictionarySequenceOrDictionary.h',
      '<(bindings_core_v8_output_dir)/EventListenerOptionsOrBoolean.cpp',
      '<(bindings_core_v8_output_dir)/EventListenerOptionsOrBoolean.h',
      '<(bindings_core_v8_output_dir)/FileOrUSVString.cpp',
      '<(bindings_core_v8_output_dir)/FileOrUSVString.h',
      '<(bindings_core_v8_output_dir)/HTMLElementOrLong.cpp',
      '<(bindings_core_v8_output_dir)/HTMLElementOrLong.h',
      '<(bindings_core_v8_output_dir)/HTMLImageElementOrHTMLVideoElementOrHTMLCanvasElementOrBlobOrImageDataOrImageBitmap.cpp',
      '<(bindings_core_v8_output_dir)/HTMLImageElementOrHTMLVideoElementOrHTMLCanvasElementOrBlobOrImageDataOrImageBitmap.h',
      '<(bindings_core_v8_output_dir)/HTMLOptionElementOrHTMLOptGroupElement.cpp',
      '<(bindings_core_v8_output_dir)/HTMLOptionElementOrHTMLOptGroupElement.h',
      '<(bindings_core_v8_output_dir)/HTMLScriptElementOrSVGScriptElement.cpp',
      '<(bindings_core_v8_output_dir)/HTMLScriptElementOrSVGScriptElement.h',
      '<(bindings_core_v8_output_dir)/NodeListOrElement.cpp',
      '<(bindings_core_v8_output_dir)/NodeListOrElement.h',
      '<(bindings_core_v8_output_dir)/NodeOrString.cpp',
      '<(bindings_core_v8_output_dir)/NodeOrString.h',
      '<(bindings_core_v8_output_dir)/RadioNodeListOrElement.cpp',
      '<(bindings_core_v8_output_dir)/RadioNodeListOrElement.h',
      '<(bindings_core_v8_output_dir)/StringOrArrayBuffer.cpp',
      '<(bindings_core_v8_output_dir)/StringOrArrayBuffer.h',
      '<(bindings_core_v8_output_dir)/StringOrArrayBufferOrArrayBufferView.cpp',
      '<(bindings_core_v8_output_dir)/StringOrArrayBufferOrArrayBufferView.h',
      '<(bindings_core_v8_output_dir)/StringOrFloat.cpp',
      '<(bindings_core_v8_output_dir)/StringOrFloat.h',
      '<(bindings_core_v8_output_dir)/USVStringOrURLSearchParams.cpp',
      '<(bindings_core_v8_output_dir)/USVStringOrURLSearchParams.h',
      '<(bindings_core_v8_output_dir)/UnrestrictedDoubleOrString.cpp',
      '<(bindings_core_v8_output_dir)/UnrestrictedDoubleOrString.h',
      '<(bindings_core_v8_output_dir)/VideoTrackOrAudioTrackOrTextTrack.cpp',
      '<(bindings_core_v8_output_dir)/VideoTrackOrAudioTrackOrTextTrack.h',
    ],

    'conditions': [
      ['OS=="win" and buildtype=="Official"', {
        # On Windows Official release builds, we try to preserve symbol
        # space.
        'bindings_core_v8_generated_aggregate_files': [
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings.cpp',
        ],
      }, {
        'bindings_core_v8_generated_aggregate_files': [
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings01.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings02.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings03.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings04.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings05.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings06.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings07.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings08.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings09.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings10.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings11.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings12.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings13.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings14.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings15.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings16.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings17.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings18.cpp',
          '<(bindings_core_v8_output_dir)/V8GeneratedCoreBindings19.cpp',
        ],
      }],
    ],
  },
}
