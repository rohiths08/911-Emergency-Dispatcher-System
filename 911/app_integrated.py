from flask import Flask, render_template, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy
import os

app = Flask(__name__)

# Database Configuration
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///cases.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'mysecretkey'

# Choose backend: 'database' or 'c_library'
BACKEND = os.environ.get('BACKEND', 'c_library')

db = SQLAlchemy(app)

# Case Model (Database Table)
class Case(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    case_type = db.Column(db.String(100), nullable=False)
    location = db.Column(db.String(100), nullable=False)
    priority = db.Column(db.Integer, nullable=False)
    department = db.Column(db.String(50), nullable=True)

    def __repr__(self):
        return f"<Case {self.id} - {self.case_type}>"

# Initialize Database (for first-time setup)
with app.app_context():
    db.create_all()

# Try to load C library
cases_lib = None
try:
    from cases_wrapper import get_cases_library
    cases_lib = get_cases_library()
    print(f"✓ C library loaded successfully! Using backend: {BACKEND}")
except Exception as e:
    print(f"⚠ C library not available: {e}. Falling back to database.")
    BACKEND = 'database'

# Helper functions for abstraction
def add_case_backend(case_type, location, priority, department):
    if BACKEND == 'c_library' and cases_lib:
        return cases_lib.add_case(case_type, location, priority, department)
    else:
        new_case = Case(case_type=case_type, location=location, priority=priority, department=department)
        db.session.add(new_case)
        db.session.commit()
        return new_case.id

def get_all_cases_backend():
    if BACKEND == 'c_library' and cases_lib:
        return cases_lib.get_all_cases()
    else:
        cases = Case.query.all()
        return [{
            'id': c.id,
            'case_type': c.case_type,
            'location': c.location,
            'priority': c.priority,
            'department': c.department or ''
        } for c in cases]

def delete_case_backend(case_id):
    if BACKEND == 'c_library' and cases_lib:
        return cases_lib.delete_case(case_id)
    else:
        case = Case.query.get(case_id)
        if case:
            db.session.delete(case)
            db.session.commit()
            return True
        return False

def assign_department_backend(case_id, department):
    if BACKEND == 'c_library' and cases_lib:
        return cases_lib.assign_department(case_id, department)
    else:
        case = Case.query.get(case_id)
        if case:
            case.department = department
            db.session.commit()
            return True
        return False

def get_statistics_backend():
    if BACKEND == 'c_library' and cases_lib:
        return cases_lib.get_statistics()
    else:
        return {
            'fire_count': Case.query.filter(Case.department.like('%Fire%')).count(),
            'healthcare_count': Case.query.filter(Case.department.like('%Healthcare%')).count(),
            'police_count': Case.query.filter(Case.department.like('%Police%')).count(),
            'high_priority': Case.query.filter_by(priority=1).count(),
            'moderate_priority': Case.query.filter_by(priority=2).count(),
            'low_priority': Case.query.filter_by(priority=3).count()
        }

def search_cases_backend(query):
    if BACKEND == 'c_library' and cases_lib:
        matching_ids = cases_lib.search_cases(query)
        all_cases = cases_lib.get_all_cases()
        return [c for c in all_cases if c['id'] in matching_ids]
    else:
        cases = Case.query.filter(
            (Case.case_type.like(f'%{query}%')) | 
            (Case.location.like(f'%{query}%'))
        ).all()
        return [{
            'id': c.id,
            'case_type': c.case_type,
            'location': c.location,
            'priority': c.priority,
            'department': c.department or ''
        } for c in cases]

# Home Route (Landing Page)
@app.route('/')
def home():
    message = request.args.get('message', '')
    backend_status = f"Using {BACKEND.upper()} backend"
    return render_template('index.html', message=message, backend=backend_status)

# Add Case Route
@app.route('/add_case', methods=['GET', 'POST'])
def add_case():
    if request.method == 'POST':
        case_type = request.form['case_type']
        location = request.form['location']
        priority = int(request.form['priority'])
        department = request.form.get('department')

        case_id = add_case_backend(case_type, location, priority, department)
        flash(f'Case #{case_id} added successfully!', 'success')
        return redirect(url_for('home', message=f'Case #{case_id} added successfully!'))

    return render_template('add_case.html')

# Display All Cases with Search Functionality
@app.route('/display_cases', methods=['GET', 'POST'])
def display_cases():
    search_query = request.args.get('search_query', '')
    
    if search_query:
        cases = search_cases_backend(search_query)
    else:
        cases = get_all_cases_backend()

    return render_template('display_cases.html', cases=cases, backend=BACKEND)

# Delete a Case
@app.route('/delete_case/<int:id>', methods=['GET'])
def delete_case(id):
    if delete_case_backend(id):
        flash('Case deleted successfully!', 'success')
    else:
        flash('Case not found!', 'error')
    return redirect(url_for('display_cases'))

# Assign Case to Department
@app.route('/assign_case/<int:id>', methods=['GET', 'POST'])
def assign_case(id):
    # Get case info
    if BACKEND == 'c_library' and cases_lib:
        all_cases = cases_lib.get_all_cases()
        case = next((c for c in all_cases if c['id'] == id), None)
    else:
        case_obj = Case.query.get(id)
        case = {
            'id': case_obj.id,
            'case_type': case_obj.case_type,
            'location': case_obj.location,
            'priority': case_obj.priority,
            'department': case_obj.department or ''
        } if case_obj else None
    
    if not case:
        flash('Case not found!', 'error')
        return redirect(url_for('display_cases'))
    
    if request.method == 'POST':
        department = request.form['department']
        
        if assign_department_backend(id, department):
            # Flash messages based on department assignment
            if 'Fire' in department:
                flash(f'Case assigned to Fire Department', 'success')
            if 'Healthcare' in department:
                flash(f'Case assigned to Healthcare Department', 'success')
            if 'Police' in department:
                flash(f'Case assigned to Police Department', 'success')
            
            flash(f'Case successfully assigned to {department}!', 'success')
        else:
            flash('Failed to assign department!', 'error')
        
        return redirect(url_for('display_cases'))
    
    return render_template('assign_case.html', case=case)

# Statistics Route
@app.route('/statistics')
def statistics():
    stats = get_statistics_backend()
    
    return render_template('statistics.html',
                           fire_count=stats['fire_count'],
                           healthcare_count=stats['healthcare_count'],
                           police_count=stats['police_count'],
                           high_priority=stats['high_priority'],
                           moderate_priority=stats['moderate_priority'],
                           low_priority=stats['low_priority'],
                           backend=BACKEND)

# Backend Toggle Route (for testing)
@app.route('/toggle_backend')
def toggle_backend():
    global BACKEND
    if cases_lib:
        BACKEND = 'database' if BACKEND == 'c_library' else 'c_library'
        flash(f'Switched to {BACKEND.upper()} backend', 'success')
    else:
        flash('C library not available. Using database only.', 'warning')
    return redirect(url_for('home'))

# Run the Flask App
if __name__ == '__main__':
    app.run(debug=True, port=5001)  # Using port 5001 to avoid conflict
