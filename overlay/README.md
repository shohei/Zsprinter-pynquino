# Overlay

- Modified Arduino IOP 
    - BRAM to 256MB
    - disconnected GPIO from A5 (swapped from U10 to T9)
        - A5 is dedicatedly used for XADC (VAUX13)
        - Same for A4 (swapped to U9)
    - Add UART1
    	 - Wired to RX/IO40, TX/IO41
