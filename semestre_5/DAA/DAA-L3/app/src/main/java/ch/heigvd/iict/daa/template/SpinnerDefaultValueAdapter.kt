package ch.heigvd.iict.daa.template

import android.content.Context
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter

/**
 * Custom ArrayAdapter for spinners with a non-selectable default placeholder value.
 * The first item acts as a default value and cannot be selected.
 *
 * @param ctx The context
 * @param defaultValue The placeholder text to display initially
 * @param entries The actual selectable values
 *
 * @author
 * - Nathan Füllemann
 * - Mathéo Lopez
 * - Arnaud Tribolet
 */
class SpinnerDefaultValueAdapter<T>(
    ctx: Context,
    defaultValue: T,
    entries: Array<T>
) : ArrayAdapter<T>(ctx, android.R.layout.simple_spinner_dropdown_item) {

    companion object {
        private const val DEFAULT_VALUE_POSITION = 0
    }

    init {
        add(defaultValue)
        addAll(*entries)
    }

    override fun getDropDownView(position: Int, convertView: View?, parent: ViewGroup): View {
        return if (position == DEFAULT_VALUE_POSITION) {
            // Creates an invisible view for the default value
            View(context).apply { visibility = View.GONE }
        } else {
            // Important: pass convertView as null to allow proper view recycling
            super.getDropDownView(position, null, parent)
        }
    }

    override fun isEnabled(position: Int): Boolean {
        // Disables the default value, only other items are selectable
        return position != DEFAULT_VALUE_POSITION && super.isEnabled(position)
    }
}
