Calibration
===========

We need to calibrate each TriPoint module to account for unique TX and RX
delays with DW1000 radios.


Process
-------

The TriPoint software includes the code needed to run calibration. Putting
the node in calibration mode requires writing the calibration node index
to the `0x3159` characteristic.

In practice, do this:

1. Make noble run without sudo:

        sudo setcap cap_net_raw+eip node_modules/noble/build/Release/hci-ble

2. Collect the data from each node:

        node ./calibration_log.js

    Make sure there are only 3 nodes on during calibration.

3. Process the data into a single file

        ./calibration_condense.py YYYY-MM-DD_HH-MM-SS

