package ch.heigvd.iict.daa.template

import android.os.Bundle
import android.util.Log
import android.view.inputmethod.EditorInfo
import android.widget.Spinner
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.Group
import ch.heigvd.iict.daa.template.databinding.ActivityMainBinding
import com.google.android.material.datepicker.CalendarConstraints
import com.google.android.material.datepicker.DateValidatorPointBackward
import com.google.android.material.datepicker.MaterialDatePicker
import java.util.Calendar
import java.util.TimeZone

/**
 * Main activity for our application, it handles the controller part of the MVC pattern.
 * @author
 * - Nathan Füllemann
 * - Mathéo Lopez
 * - Arnaud Tribolet
 */
class MainActivity : AppCompatActivity() {

    companion object {
        private val utcTimezone = TimeZone.getTimeZone("UTC")
        private val utcDateFormatter = Person.dateFormatter.apply { timeZone = utcTimezone }
    }

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setSupportActionBar(binding.toolbar)

        setupSpinners()
        setupSectionVisibility()
        setupDatePicker()
        setupButtons()
        setupDoneButtonAfterRemark()
        displayExampleStudent()
    }

    /**
     * Sets all fields according to exampleStudent
     */
    private fun displayExampleStudent() {
        binding.inputLastName.setText(Person.exampleStudent.name)
        binding.inputFirstName.setText(Person.exampleStudent.firstName)
        binding.inputBirthdate.setText(utcDateFormatter.format(Person.exampleStudent.birthDay.time))
        val nationalities = resources.getStringArray(R.array.nationalities)
        val index = nationalities.indexOfFirst { it.equals(Person.exampleStudent.nationality, ignoreCase = true) }
        if (index >= 0) {
            binding.inputNationality.setSelection(index)
        }
        binding.inputOccupation.check(R.id.radioStudent)
        binding.inputSchool.setText(Person.exampleStudent.university)
        binding.inputGradYear.setText(Person.exampleStudent.graduationYear.toString())
        binding.inputEmail.setText(Person.exampleStudent.email)
        binding.inputComments.setText(Person.exampleStudent.remark)
    }

    /**
     * Sets up the spinners with default values
     */
    private fun setupSpinners() {
        setupSpinner(
            binding.inputNationality,
            R.string.nationality_empty,
            R.array.nationalities
        )
        setupSpinner(
            binding.inputSector,
            R.string.sectors_empty,
            R.array.sectors
        )
    }

    /**
     * Helper function to setup a spinner with default value
     */
    private fun setupSpinner(spinner: Spinner, emptyLabelId: Int, arrayId: Int) {
        spinner.adapter = SpinnerDefaultValueAdapter(
            this,
            resources.getString(emptyLabelId),
            resources.getStringArray(arrayId)
        )
    }

    /**
     * Sets up the visibility toggle for student/worker specific sections
     */
    private fun setupSectionVisibility() {
        binding.inputOccupation.setOnCheckedChangeListener { _, checkedId ->
            val isStudent = checkedId == R.id.radioStudent
            val isEmployee = checkedId == R.id.radioEmployee

            binding.studentSpecificGroup.visibility = if (isStudent) Group.VISIBLE else Group.GONE
            binding.workerSpecificGroup.visibility = if (isEmployee) Group.VISIBLE else Group.GONE
        }

        hideSpecificGroups()
    }

    /**
     * Hides all specific groups on initialization
     */
    private fun hideSpecificGroups() {
        binding.studentSpecificGroup.visibility = Group.GONE
        binding.workerSpecificGroup.visibility = Group.GONE
    }

    /**
     * Sets up the date picker interaction
     */
    private fun setupDatePicker() {
        binding.birthDateButton.setOnClickListener {
            openDatePicker()
        }

        binding.birthDateButton.setOnFocusChangeListener { _, hasFocus ->
            if (hasFocus) {
                openDatePicker()
            }
        }
    }

    /**
     * Sets up the button click listeners
     */
    private fun setupButtons() {
        binding.buttonOk.setOnClickListener { saveData() }
        binding.buttonCancel.setOnClickListener { clearForm() }
    }

    /**
     * Sets up the automatic validation when done button is pressed
     */
    private fun setupDoneButtonAfterRemark() {
        binding.inputComments.setOnEditorActionListener { _, action, _ ->
            if (action == EditorInfo.IME_ACTION_DONE) {
                binding.buttonOk.performClick()
                true
            } else {
                false
            }
        }
    }

    /**
     * Opens the date picker dialog
     */
    private fun openDatePicker() {
        val utcCalendar = Calendar.getInstance(utcTimezone)
        var currentTimestamp = MaterialDatePicker.todayInUtcMilliseconds()

        if (binding.inputBirthdate.text.isNotEmpty()) {
            val date = utcDateFormatter.parse(binding.inputBirthdate.text.toString())
            if (date != null) {
                currentTimestamp = date.time
            }
        }

        val datePicker = MaterialDatePicker.Builder.datePicker()
            .setTitleText(R.string.main_base_birthdate_dialog_title)
            .setCalendarConstraints(buildCalendarConstraints(utcCalendar))
            .setSelection(currentTimestamp)
            .build()

        datePicker.show(supportFragmentManager, "birthDate")
        datePicker.addOnPositiveButtonClickListener {
            binding.birthDateButton.clearFocus()
            utcCalendar.timeInMillis = it
            binding.inputBirthdate.setText(utcDateFormatter.format(utcCalendar.time))
            binding.inputNationality.requestFocus()
        }
    }

    /**
     * Builds calendar constraints for the date picker
     */
    private fun buildCalendarConstraints(calendar: Calendar): CalendarConstraints {
        return CalendarConstraints.Builder()
            .setOpenAt(MaterialDatePicker.todayInUtcMilliseconds())
            .setValidator(DateValidatorPointBackward.now())
            .setStart(calendar.apply { add(Calendar.YEAR, -110) }.timeInMillis)
            .setEnd(MaterialDatePicker.todayInUtcMilliseconds())
            .build()
    }

    /**
     * Saves the form data based on occupation type
     */
    private fun saveData() {
        if (!validateInput()) return

        when (binding.inputOccupation.checkedRadioButtonId) {
            R.id.radioStudent -> saveStudent()
            R.id.radioEmployee -> saveWorker()
        }
    }

    /**
     * Validates all form inputs
     */
    private fun validateInput(): Boolean {
        val lastName = binding.inputLastName.text.toString()
        val firstName = binding.inputFirstName.text.toString()
        val date = binding.inputBirthdate.text.toString()

        if (!validateNonEmpty(lastName, firstName, date, message = "Veuillez remplir tous les champs obligatoires")) {
            return false
        }

        if (!isSpinnerSelected(binding.inputNationality)) {
            toast("Veuillez sélectionner une nationalité")
            return false
        }

        return when (binding.inputOccupation.checkedRadioButtonId) {
            R.id.radioStudent -> validateStudentFields()
            R.id.radioEmployee -> validateWorkerFields()
            else -> {
                toast("Veuillez sélectionner une occupation")
                false
            }
        }
    }

    /**
     * Validates student-specific fields
     */
    private fun validateStudentFields(): Boolean {
        val school = binding.inputSchool.text.toString()
        val gradYear = binding.inputGradYear.text.toString()

        if (!validateNonEmpty(school, gradYear, message = "Veuillez remplir tous les champs étudiant")) {
            return false
        }
        return true
    }

    /**
     * Validates worker-specific fields
     */
    private fun validateWorkerFields(): Boolean {
        val company = binding.inputCompany.text.toString()
        val experience = binding.inputExperience.text.toString()

        if (!validateNonEmpty(company, experience, message = "Veuillez remplir tous les champs employé")) {
            return false
        }

        if (!isSpinnerSelected(binding.inputSector)) {
            toast("Veuillez sélectionner un secteur d'activité")
            return false
        }
        return true
    }

    /**
     * Validates that all provided fields are non-empty
     */
    private fun validateNonEmpty(vararg fields: String, message: String): Boolean {
        if (fields.any { it.isEmpty() }) {
            toast(message)
            return false
        }
        return true
    }

    /**
     * Checks if a spinner has a valid selection (not the default placeholder)
     */
    private fun isSpinnerSelected(spinner: Spinner): Boolean {
        return spinner.selectedItemPosition != 0
    }

    /**
     * Saves student information
     */
    private fun saveStudent() {
        val student = Student(
            binding.inputLastName.text.toString(),
            binding.inputFirstName.text.toString(),
            binding.inputBirthdate.text.toString().toCalendar(),
            binding.inputNationality.selectedItem.toString(),
            binding.inputSchool.text.toString(),
            binding.inputGradYear.text.toString().toInt(),
            binding.inputEmail.text.toString(),
            binding.inputComments.text.toString()
        )

        logAndNotifySave(student, "Étudiant sauvegardé avec succès")
    }

    /**
     * Saves worker information
     */
    private fun saveWorker() {
        val worker = Worker(
            binding.inputLastName.text.toString(),
            binding.inputFirstName.text.toString(),
            binding.inputBirthdate.text.toString().toCalendar(),
            binding.inputNationality.selectedItem.toString(),
            binding.inputCompany.text.toString(),
            binding.inputSector.selectedItem.toString(),
            binding.inputExperience.text.toString().toInt(),
            binding.inputEmail.text.toString(),
            binding.inputComments.text.toString()
        )

        logAndNotifySave(worker, "Employé sauvegardé avec succès")
    }

    /**
     * Logs the saved person and displays a success message
     */
    private fun logAndNotifySave(person: Person, message: String) {
        Log.i("[SAVED ${person::class.simpleName}]", person.toString())
        toast(message)
    }

    /**
     * Clears all form fields
     */
    private fun clearForm() {
        binding.apply {
            inputLastName.text.clear()
            inputFirstName.text.clear()
            inputBirthdate.text.clear()
            inputNationality.setSelection(0)
            inputOccupation.clearCheck()
            inputSchool.text.clear()
            inputGradYear.text.clear()
            inputCompany.text.clear()
            inputSector.setSelection(0)
            inputExperience.text.clear()
            inputEmail.text.clear()
            inputComments.text.clear()
        }
    }

    /**
     * Extension function to convert a string to a calendar
     */
    private fun String.toCalendar(): Calendar {
        val calendar = Calendar.getInstance(utcTimezone)
        val date = utcDateFormatter.parse(this)
        if (date != null) {
            calendar.time = date
        }
        return calendar
    }

    /**
     * Displays a toast message
     */
    private fun toast(message: String, length: Int = Toast.LENGTH_SHORT) {
        Toast.makeText(this, message, length).show()
    }
}
