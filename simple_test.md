# Simple Real-Time Testing

Since a full 49.7-day test isn't practical, here are shorter tests:

## Quick Verification Tests (5-10 minutes each)

### Test 1: Manual Recovery
1. Press wall button 4 times quickly
2. Wait 4 seconds (past the 3-second timeout)
3. Press wall button once more
4. **Expected**: Should start new 3-second window, not enter recovery mode

### Test 2: Motion Timer
1. Trigger motion detection
2. Wait exactly 6 seconds
3. **Expected**: Motion should clear after 5 seconds, not before or after

### Test 3: WiFi Settings
1. Change WiFi settings in web interface
2. Observe 30-second timeout behavior
3. **Expected**: Should attempt reconnection after exactly 30 seconds

### Test 4: Status Timeout
1. Reboot device
2. Monitor serial output
3. **Expected**: Should see "Status timeout, starting homekit" after 2 seconds

## Stress Test
1. Leave device running for 24-48 hours
2. Periodically test manual recovery and motion detection
3. Monitor for any timing anomalies
4. Check that all features work consistently

## Success Indicators
- Consistent timing behavior
- No "stuck" states
- All timeouts work as expected
- No crashes or hangs related to timing