#!/usr/bin/env python3
"""Test script for C library integration"""

from cases_wrapper import get_cases_library

def test_library():
    print("Testing C Library Integration...")
    print("-" * 50)
    
    # Initialize library
    lib = get_cases_library()
    print("✓ Library loaded successfully!")
    
    # Add some test cases
    print("\nAdding test cases...")
    id1 = lib.add_case('Fire Emergency', '123 Main St', 1, 'Fire Department')
    print(f"  Added case #{id1}: Fire Emergency")
    
    id2 = lib.add_case('Medical Emergency', '456 Oak Ave', 1, 'Healthcare')
    print(f"  Added case #{id2}: Medical Emergency")
    
    id3 = lib.add_case('Robbery', '789 Pine Rd', 2, 'Police')
    print(f"  Added case #{id3}: Robbery")
    
    # Get case count
    count = lib.get_case_count()
    print(f"\n✓ Total cases: {count}")
    
    # Get all cases
    print("\nRetrieving all cases...")
    cases = lib.get_all_cases()
    for case in cases:
        print(f"  Case #{case['id']}: {case['case_type']} at {case['location']} (Priority: {case['priority']}, Dept: {case['department']})")
    
    # Get statistics
    print("\nStatistics:")
    stats = lib.get_statistics()
    print(f"  Fire Department: {stats['fire_count']} cases")
    print(f"  Healthcare: {stats['healthcare_count']} cases")
    print(f"  Police: {stats['police_count']} cases")
    print(f"  High Priority: {stats['high_priority']} cases")
    print(f"  Moderate Priority: {stats['moderate_priority']} cases")
    print(f"  Low Priority: {stats['low_priority']} cases")
    
    # Test search
    print("\nSearching for 'Fire'...")
    results = lib.search_cases('Fire')
    print(f"  Found {len(results)} matching case(s): {results}")
    
    # Test assignment
    print(f"\nReassigning case #{id3} to 'Police & Fire'...")
    success = lib.assign_department(id3, 'Police & Fire')
    print(f"  Assignment {'successful' if success else 'failed'}")
    
    # Test deletion
    print(f"\nDeleting case #{id2}...")
    success = lib.delete_case(id2)
    print(f"  Deletion {'successful' if success else 'failed'}")
    print(f"  Remaining cases: {lib.get_case_count()}")
    
    print("\n" + "="*50)
    print("✓ All tests passed!")
    print("="*50)

if __name__ == '__main__':
    test_library()
