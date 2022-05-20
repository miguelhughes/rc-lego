
BT/usb errors & application behavior

ACL data in error:
(BTD.cpp ln 1100)
HCI event error:
(BTD.cpp ln 763)

without changes or error handling app behavior:
sometimes continues working, sometimes doesn't:
ACL data in error: F0

stops working:
HCI event error: F0
ACL data in error: F0
ACL data in error: 03
HCI event error: 03
-----
code changes: add callback on btd.cpp to be able to add an error handler.

PS3.disconnect() on error
except for acl && 0
ACL data in error: F0 - ok x 2
HCI event error: F0 - ok
ACL data in error: 0F - freeze. dongle light off. x 2

except for acl && 0xF0
ACL data in error: 03 - freeze. dongle light off.

ACL data in error: F0 along with HCI event error: 03 - freeze. dongle light off