to do Telnet unlock -

mrUNLOCK -run "UNLOCK-TELNET" -sgm xx

where sgm is the device model, please refer to mrUNLOCK.SCR

to do SIM unlock -

mrUNLOCK -run "SIM-UNLOCK" -sgm xx

No existing script for IMEI repair, please create your own to proceed the function

*Reset CNDKey for legacy, AirCard, models (to enable advanced AT commands) -

mrUNLOCK -run "SET-CND-KEY" -sgm xx (need to modify new-CND-Key in mrUNLOCK.SCR)
