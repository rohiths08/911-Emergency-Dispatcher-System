from flask import Flask, render_template, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

# Database Configuration
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///cases.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'mysecretkey'
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

# Home Route (Landing Page)
@app.route('/')
def home():
    message = request.args.get('message', '')  # To pass message after action (like adding a case)
    return render_template('index.html', message=message)

# Add Case Route
@app.route('/add_case', methods=['GET', 'POST'])
def add_case():
    if request.method == 'POST':
        case_type = request.form['case_type']
        location = request.form['location']
        priority = int(request.form['priority'])
        department = request.form.get('department')

        new_case = Case(case_type=case_type, location=location, priority=priority, department=department)
        db.session.add(new_case)
        db.session.commit()
        flash('Case added successfully!', 'success')
        return redirect(url_for('home', message='Case added successfully!'))

    return render_template('add_case.html')

# Display All Cases with Search Functionality
@app.route('/display_cases', methods=['GET', 'POST'])
def display_cases():
    search_query = request.args.get('search_query', '')
    if search_query:
        cases = Case.query.filter(
            (Case.case_type.like(f'%{search_query}%')) | 
            (Case.location.like(f'%{search_query}%'))
        ).all()
    else:
        cases = Case.query.all()

    return render_template('display_cases.html', cases=cases)

# Delete a Case
@app.route('/delete_case/<int:id>', methods=['GET'])
def delete_case(id):
    case = Case.query.get(id)
    if case:
        db.session.delete(case)
        db.session.commit()
        flash('Case deleted successfully!', 'success')
    return redirect(url_for('display_cases'))

# Assign Case to Department
@app.route('/assign_case/<int:id>', methods=['GET', 'POST'])
def assign_case(id):
    case = Case.query.get(id)
    if request.method == 'POST':
        department = request.form['department']
        case.department = department

        # Logic to display flash messages based on department assignment
        if 'Fire' in department:
            flash(f'Case assigned to Fire Department', 'success')
        if 'Healthcare' in department:
            flash(f'Case assigned to Healthcare Department', 'success')
        if 'Police' in department:
            flash(f'Case assigned to Police Department', 'success')

        db.session.commit()
        flash(f'Case successfully assigned to {department}!', 'success')
        return redirect(url_for('display_cases'))
    return render_template('assign_case.html', case=case)

# Statistics Route
@app.route('/statistics')
def statistics():
    fire_count = Case.query.filter(Case.department.like('%Fire%')).count()
    healthcare_count = Case.query.filter(Case.department.like('%Healthcare%')).count()
    police_count = Case.query.filter(Case.department.like('%Police%')).count()
    
    high_priority = Case.query.filter_by(priority=1).count()
    moderate_priority = Case.query.filter_by(priority=2).count()
    low_priority = Case.query.filter_by(priority=3).count()

    return render_template('statistics.html', fire_count=fire_count, healthcare_count=healthcare_count, police_count=police_count,
                           high_priority=high_priority, moderate_priority=moderate_priority, low_priority=low_priority)

# Run the Flask App
if __name__ == '__main__':
    app.run(debug=True)
