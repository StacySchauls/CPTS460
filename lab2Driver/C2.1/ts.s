.text
.global start

start:
  mov r0, #1
  MOV R1, #2
  ADD R1, R1, R0
  ldr r2, =result
  str r1, [r2]

stop: b stop
  .data
result: .word 0
