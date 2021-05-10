#ifndef WASMTIME_VAL_H
#define WASMTIME_VAL_H

#include <wasm.h>
#include <wasmtime/extern.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wasmtime_externref wasmtime_externref_t;

/**
 * \brief Create a new `externref` value with a finalizer.
 *
 * TODO
 *
 * Creates a new `externref` value wrapping the provided data, and writes it to
 * `valp`.
 *
 * When the reference is reclaimed, the wrapped data is cleaned up with the
 * provided finalizer. If you do not need to clean up the wrapped data, then use
 * #wasmtime_externref_new.
 *
 * Gives ownership of the newly created `externref` value.
 */
WASM_API_EXTERN wasmtime_externref_t *wasmtime_externref_new(void *data, void (*finalizer)(void*));

/**
 * \brief Get an `externref`'s wrapped data
 *
 * TODO
 *
 * If the given value is a reference to a non-null `externref`, writes the
 * wrapped data that was passed into #wasmtime_externref_new or
 * #wasmtime_externref_new_with_finalizer when creating the given `externref` to
 * `datap`, and returns `true`.
 *
 * If the value is a reference to a null `externref`, writes `NULL` to `datap`
 * and returns `true`.
 *
 * If the given value is not an `externref`, returns `false` and leaves `datap`
 * unmodified.
 *
 * Does not take ownership of `val`. Does not give up ownership of the `void*`
 * data written to `datap`.
 *
 * Both `val` and `datap` must not be `NULL`.
 */
WASM_API_EXTERN void *wasmtime_externref_data(wasmtime_externref_t *data);

WASM_API_EXTERN wasmtime_externref_t *wasmtime_externref_clone(wasmtime_externref_t *ref);

/**
 * TODO
 */
WASM_API_EXTERN void wasmtime_externref_delete(wasmtime_externref_t *ref);

typedef enum wasmtime_valkind {
  WASMTIME_I32,
  WASMTIME_I64,
  WASMTIME_F32,
  WASMTIME_F64,
  WASMTIME_V128,
  WASMTIME_FUNCREF,
  WASMTIME_EXTERNREF,
} wasmtime_valkind_t;

typedef uint8_t wasmtime_v128[16];

typedef union wasmtime_valunion {
  int32_t i32;
  int64_t i64;
  float32_t f32;
  float64_t f64;
  wasmtime_func_t funcref;
  wasmtime_externref_t *externref;
  wasmtime_v128 v128;
} wasmtime_valunion_t;

typedef struct wasmtime_val {
  wasmtime_valkind_t kind;
  wasmtime_valunion_t of;
} wasmtime_val_t;

#define WASMTIME_FUNCREF_NULL ((uint64_t) -1)
/**
 * TODO
 */
WASM_API_EXTERN void wasmtime_val_delete(wasmtime_val_t *val);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif // WASMTIME_VAL_H

