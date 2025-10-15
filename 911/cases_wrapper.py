"""
Python wrapper for C cases library using ctypes
"""
import ctypes
import os
from typing import List, Dict, Optional

class CasesLibrary:
    def __init__(self, lib_path='./libcases.so'):
        """Initialize the C library wrapper"""
        if not os.path.exists(lib_path):
            raise FileNotFoundError(f"Shared library not found: {lib_path}")
        
        self.lib = ctypes.CDLL(lib_path)
        self._setup_function_signatures()
    
    def _setup_function_signatures(self):
        """Define function signatures for ctypes"""
        # add_case(case_type, location, priority, department) -> int
        self.lib.add_case.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]
        self.lib.add_case.restype = ctypes.c_int
        
        # get_case_count() -> int
        self.lib.get_case_count.argtypes = []
        self.lib.get_case_count.restype = ctypes.c_int
        
        # delete_case(id) -> int
        self.lib.delete_case.argtypes = [ctypes.c_int]
        self.lib.delete_case.restype = ctypes.c_int
        
        # assign_department(id, department) -> int
        self.lib.assign_department.argtypes = [ctypes.c_int, ctypes.c_char_p]
        self.lib.assign_department.restype = ctypes.c_int
        
        # get_all_cases(ids, types, locations, priorities, departments, max_cases) -> int
        self.lib.get_all_cases.argtypes = [
            ctypes.POINTER(ctypes.c_int),
            ctypes.c_char_p,
            ctypes.c_char_p,
            ctypes.POINTER(ctypes.c_int),
            ctypes.c_char_p,
            ctypes.c_int
        ]
        self.lib.get_all_cases.restype = ctypes.c_int
        
        # get_statistics(stats) -> void
        self.lib.get_statistics.argtypes = [ctypes.POINTER(ctypes.c_int)]
        self.lib.get_statistics.restype = None
        
        # clear_all_cases() -> void
        self.lib.clear_all_cases.argtypes = []
        self.lib.clear_all_cases.restype = None
        
        # search_cases_by_query(query, result_ids, max_results) -> int
        self.lib.search_cases_by_query.argtypes = [ctypes.c_char_p, ctypes.POINTER(ctypes.c_int), ctypes.c_int]
        self.lib.search_cases_by_query.restype = ctypes.c_int
    
    def add_case(self, case_type: str, location: str, priority: int, department: Optional[str] = None) -> int:
        """Add a new case to the C library"""
        dept = department.encode('utf-8') if department else None
        return self.lib.add_case(
            case_type.encode('utf-8'),
            location.encode('utf-8'),
            priority,
            dept
        )
    
    def get_case_count(self) -> int:
        """Get total number of cases"""
        return self.lib.get_case_count()
    
    def delete_case(self, case_id: int) -> bool:
        """Delete a case by ID"""
        return self.lib.delete_case(case_id) == 1
    
    def assign_department(self, case_id: int, department: str) -> bool:
        """Assign a department to a case"""
        return self.lib.assign_department(case_id, department.encode('utf-8')) == 1
    
    def get_all_cases(self) -> List[Dict]:
        """Get all cases as a list of dictionaries"""
        max_cases = 1000
        
        # Allocate buffers
        ids = (ctypes.c_int * max_cases)()
        priorities = (ctypes.c_int * max_cases)()
        types = ctypes.create_string_buffer(max_cases * 100)
        locations = ctypes.create_string_buffer(max_cases * 100)
        departments = ctypes.create_string_buffer(max_cases * 100)
        
        # Call C function
        count = self.lib.get_all_cases(ids, types, locations, priorities, departments, max_cases)
        
        # Parse results
        cases = []
        for i in range(count):
            case = {
                'id': ids[i],
                'case_type': types.raw[i*100:(i+1)*100].split(b'\0')[0].decode('utf-8'),
                'location': locations.raw[i*100:(i+1)*100].split(b'\0')[0].decode('utf-8'),
                'priority': priorities[i],
                'department': departments.raw[i*100:(i+1)*100].split(b'\0')[0].decode('utf-8')
            }
            cases.append(case)
        
        return cases
    
    def get_statistics(self) -> Dict[str, int]:
        """Get department and priority statistics"""
        stats = (ctypes.c_int * 6)()
        self.lib.get_statistics(stats)
        
        return {
            'fire_count': stats[0],
            'healthcare_count': stats[1],
            'police_count': stats[2],
            'high_priority': stats[3],
            'moderate_priority': stats[4],
            'low_priority': stats[5]
        }
    
    def clear_all_cases(self):
        """Clear all cases from memory"""
        self.lib.clear_all_cases()
    
    def search_cases(self, query: str) -> List[int]:
        """Search cases by query string, returns list of matching case IDs"""
        max_results = 1000
        result_ids = (ctypes.c_int * max_results)()
        
        count = self.lib.search_cases_by_query(query.encode('utf-8'), result_ids, max_results)
        
        return [result_ids[i] for i in range(count)]


# Singleton instance
_cases_lib = None

def get_cases_library() -> CasesLibrary:
    """Get or create singleton instance of CasesLibrary"""
    global _cases_lib
    if _cases_lib is None:
        _cases_lib = CasesLibrary()
    return _cases_lib
