#include <stdio.h>
#include <stdint.h>

int main() {
    // Debug the rollover case
    uint32_t start_time = 0xFFFFFFFE; // 2 seconds before rollover
    uint32_t current_time = 0x00000001; // 1 second after rollover
    uint32_t duration = 2000;
    
    printf("start_time: 0x%08X (%u)\n", start_time, start_time);
    printf("current_time: 0x%08X (%u)\n", current_time, current_time);
    printf("duration: %u\n", duration);
    
    uint32_t elapsed = current_time - start_time;
    printf("elapsed (unsigned): 0x%08X (%u)\n", elapsed, elapsed);
    
    bool timeout_new = (elapsed >= duration);
    printf("timeout_new: %d\n", timeout_new);
    
    // The issue: I used milliseconds but the values are way larger
    // Let me fix the test with proper millisecond values
    
    printf("\n--- Fixed test ---\n");
    start_time = 0xFFFFF000; // Near rollover
    current_time = 0x00001000; // After rollover  
    duration = 2000; // 2 seconds in milliseconds
    
    printf("start_time: 0x%08X (%u)\n", start_time, start_time);
    printf("current_time: 0x%08X (%u)\n", current_time, current_time);
    elapsed = current_time - start_time;
    printf("elapsed: 0x%08X (%u)\n", elapsed, elapsed);
    timeout_new = (elapsed >= duration);
    printf("timeout (elapsed >= %u): %d\n", duration, timeout_new);
    
    return 0;
}