// Unit test for rollover-safe timing
#include <stdio.h>
#include <stdint.h>

// Simulate the timing patterns used in the fix
bool test_rollover_safe_timing() {
    printf("Testing rollover-safe timing patterns...\n");
    
    // Test case 1: Normal operation (no rollover)
    uint32_t start_time = 1000;
    uint32_t current_time = 4000;
    uint32_t duration = 2000;
    
    bool timeout_old = (current_time > start_time + duration); // Direct comparison
    bool timeout_new = (current_time - start_time >= duration); // Rollover-safe
    
    printf("Normal case: old=%d, new=%d (should both be true)\n", timeout_old, timeout_new);
    if (timeout_old != timeout_new) return false;
    
    // Test case 2: Rollover scenario
    start_time = 0xFFFFFFFE; // 2 seconds before rollover
    current_time = 0x00000001; // 1 second after rollover (total elapsed: 3 seconds)
    duration = 2000;
    
    timeout_old = (current_time > start_time + duration); // Would be false (broken)
    timeout_new = (current_time - start_time >= duration); // Should be true (works)
    
    printf("Rollover case: old=%d, new=%d (old should be false, new should be true)\n", 
           timeout_old, timeout_new);
    if (timeout_old != false || timeout_new != true) return false;
    
    // Test case 3: Signed cast for absolute timeouts
    uint32_t timeout_abs = 0xFFFFFFFE; // Absolute time before rollover
    current_time = 0x00000001; // After rollover
    
    bool expired_old = (current_time > timeout_abs); // Would be false (broken)
    bool expired_new = ((int32_t)(current_time - timeout_abs) >= 0); // Should be true (works)
    
    printf("Absolute timeout: old=%d, new=%d (old should be false, new should be true)\n",
           expired_old, expired_new);
    if (expired_old != false || expired_new != true) return false;
    
    return true;
}

int main() {
    if (test_rollover_safe_timing()) {
        printf("✓ All rollover timing tests passed!\n");
        return 0;
    } else {
        printf("✗ Rollover timing tests failed!\n");
        return 1;
    }
}

// Compile with: gcc -o test rollover_unit_test.cpp && ./test