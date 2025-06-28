# Millis Rollover Test Plan

## Test Setup
1. Apply rollover simulation patch
2. Build with `-D TEST_ROLLOVER` flag
3. Flash to device
4. Device will start ~60 seconds before rollover

## Test Cases

### 1. Manual Recovery Test
**Objective**: Verify manual_recovery() works across rollover
- Press wall button 5 times within 3 seconds, wait for rollover
- Should enter WiFi recovery mode correctly
- **Expected**: Recovery triggered regardless of rollover timing

### 2. WiFi Timeout Test  
**Objective**: Verify WiFi reconnection works across rollover
- Change WiFi settings via web interface
- Wait for rollover during 30-second timeout
- **Expected**: WiFi should reconnect after timeout, not hang indefinitely

### 3. Motion Timer Test
**Objective**: Verify motion detection clears properly
- Trigger motion detection (if available)
- Wait for rollover during 5-second motion timer
- **Expected**: Motion should clear 5 seconds after trigger, regardless of rollover

### 4. Soft AP Mode Test
**Objective**: Verify device reboots after 10 minutes in AP mode
- Put device in soft AP mode
- **Note**: This test would take too long, verify code logic instead

### 5. LED Flash Test
**Objective**: Verify LED timing works across rollover
- Trigger LED flash (via status change)
- Wait for rollover during flash duration
- **Expected**: LED should turn off at correct time

### 6. Status Timeout Test
**Objective**: Verify HomeKit starts after status timeout
- Boot device, wait for rollover during 2-second status timeout
- **Expected**: HomeKit should start after 2 seconds regardless of rollover

## Monitoring

Watch serial output for:
```
Push count start
Push count reset  
WiFi connecting messages
Motion Cleared
Status timeout, starting homekit
```

## Success Criteria
- All timeouts work correctly before, during, and after rollover
- No infinite waits or premature timeouts
- All timing-dependent features function normally
- Serial output shows expected timing behavior