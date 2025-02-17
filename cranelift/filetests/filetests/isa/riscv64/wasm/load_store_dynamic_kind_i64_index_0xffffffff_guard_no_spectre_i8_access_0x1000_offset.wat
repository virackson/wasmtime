;;! target = "riscv64"
;;!
;;! settings = ['enable_heap_access_spectre_mitigation=false']
;;!
;;! compile = true
;;!
;;! [globals.vmctx]
;;! type = "i64"
;;! vmctx = true
;;!
;;! [globals.heap_base]
;;! type = "i64"
;;! load = { base = "vmctx", offset = 0, readonly = true }
;;!
;;! [globals.heap_bound]
;;! type = "i64"
;;! load = { base = "vmctx", offset = 8, readonly = true }
;;!
;;! [[heaps]]
;;! base = "heap_base"
;;! min_size = 0x10000
;;! offset_guard_size = 0xffffffff
;;! index_type = "i64"
;;! style = { kind = "dynamic", bound = "heap_bound" }

;; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;; !!! GENERATED BY 'make-load-store-tests.sh' DO NOT EDIT !!!
;; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

(module
  (memory i64 1)

  (func (export "do_store") (param i64 i32)
    local.get 0
    local.get 1
    i32.store8 offset=0x1000)

  (func (export "do_load") (param i64) (result i32)
    local.get 0
    i32.load8_u offset=0x1000))

;; function u0:0:
;; block0:
;;   ld t4,8(a2)
;;   lui t3,1048575
;;   addi t3,t3,4095
;;   add t1,t4,t3
;;   ule t4,a0,t1##ty=i64
;;   bne t4,zero,taken(label1),not_taken(label3)
;; block1:
;;   ld t0,0(a2)
;;   add t0,t0,a0
;;   lui t4,1
;;   add t1,t0,t4
;;   sb a1,0(t1)
;;   j label2
;; block2:
;;   ret
;; block3:
;;   udf##trap_code=heap_oob
;;
;; function u0:1:
;; block0:
;;   ld t4,8(a1)
;;   lui t3,1048575
;;   addi t3,t3,4095
;;   add t1,t4,t3
;;   ule t4,a0,t1##ty=i64
;;   bne t4,zero,taken(label1),not_taken(label3)
;; block1:
;;   ld t0,0(a1)
;;   add t0,t0,a0
;;   lui t4,1
;;   add t1,t0,t4
;;   lbu a0,0(t1)
;;   j label2
;; block2:
;;   ret
;; block3:
;;   udf##trap_code=heap_oob